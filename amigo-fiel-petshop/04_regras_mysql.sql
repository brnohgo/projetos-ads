USE amigo_fiel_petshop;
DELIMITER $$
CREATE TRIGGER trg_agenda_insert BEFORE INSERT ON agendamento FOR EACH ROW
BEGIN
 IF NEW.status IN ('pendente','confirmado','em_atendimento') AND EXISTS (SELECT 1 FROM agendamento a WHERE a.id_funcionario=NEW.id_funcionario AND a.status IN ('pendente','confirmado','em_atendimento') AND NEW.inicio<a.fim AND NEW.fim>a.inicio) THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Conflito de horario'; END IF;
END$$
CREATE TRIGGER trg_agenda_update BEFORE UPDATE ON agendamento FOR EACH ROW
BEGIN
 IF NEW.status IN ('pendente','confirmado','em_atendimento') AND EXISTS (SELECT 1 FROM agendamento a WHERE a.id_agendamento<>OLD.id_agendamento AND a.id_funcionario=NEW.id_funcionario AND a.status IN ('pendente','confirmado','em_atendimento') AND NEW.inicio<a.fim AND NEW.fim>a.inicio) THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Conflito de horario'; END IF;
END$$
CREATE TRIGGER trg_atendimento_insert BEFORE INSERT ON atendimento FOR EACH ROW
BEGIN
 IF (SELECT status FROM agendamento WHERE id_agendamento=NEW.id_agendamento)<>'confirmado' THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Agendamento nao confirmado'; END IF;
END$$
CREATE TRIGGER trg_venda_validar BEFORE UPDATE ON venda FOR EACH ROW
BEGIN
 IF OLD.status IN ('concluida','cancelada') AND NEW.status='aberta' THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Nao pode reabrir venda'; END IF;
 IF NEW.status='concluida' AND OLD.status='aberta' THEN
  IF NOT EXISTS(SELECT 1 FROM item_venda WHERE id_venda=OLD.id_venda) THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Venda sem itens'; END IF;
  IF EXISTS(SELECT 1 FROM item_venda i JOIN produto p ON p.id_produto=i.id_produto WHERE i.id_venda=OLD.id_venda AND (i.quantidade>p.estoque_atual OR p.status<>'ativo')) THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Estoque insuficiente'; END IF;
  IF ABS(NEW.valor_total-(SELECT SUM(subtotal) FROM item_venda WHERE id_venda=OLD.id_venda)+NEW.desconto)>0.009 THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Total incorreto'; END IF;
  IF NEW.desconto>(SELECT SUM(subtotal)*0.1 FROM item_venda WHERE id_venda=OLD.id_venda) AND NEW.autorizada_por IS NULL THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Desconto exige autorizacao'; END IF;
  IF COALESCE((SELECT SUM(valor) FROM pagamento WHERE id_venda=OLD.id_venda AND status='aprovado'),0)+0.009<NEW.valor_total THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Pagamento insuficiente'; END IF;
 END IF;
 IF NEW.status='cancelada' AND OLD.status<>'cancelada' AND (NEW.motivo_cancelamento IS NULL OR TRIM(NEW.motivo_cancelamento)='' OR NEW.cancelada_por IS NULL OR NEW.data_cancelamento IS NULL) THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Cancelamento exige motivo, usuario e data'; END IF;
END$$
CREATE TRIGGER trg_venda_baixa AFTER UPDATE ON venda FOR EACH ROW
BEGIN
 IF NEW.status='concluida' AND OLD.status='aberta' THEN
  UPDATE produto p JOIN item_venda i ON i.id_produto=p.id_produto SET p.estoque_atual=p.estoque_atual-i.quantidade WHERE i.id_venda=NEW.id_venda;
  INSERT INTO movimentacao_estoque(id_produto,id_venda,id_funcionario,tipo,quantidade,motivo) SELECT id_produto,NEW.id_venda,NEW.id_funcionario,'saida',quantidade,'Baixa automatica por venda' FROM item_venda WHERE id_venda=NEW.id_venda;
 END IF;
 IF NEW.status='cancelada' AND OLD.status='concluida' THEN
  UPDATE produto p JOIN item_venda i ON i.id_produto=p.id_produto SET p.estoque_atual=p.estoque_atual+i.quantidade WHERE i.id_venda=NEW.id_venda;
  INSERT INTO movimentacao_estoque(id_produto,id_venda,id_funcionario,tipo,quantidade,motivo) SELECT id_produto,NEW.id_venda,NEW.cancelada_por,'estorno',quantidade,'Estorno de venda cancelada' FROM item_venda WHERE id_venda=NEW.id_venda;
 END IF;
 IF NEW.status='cancelada' AND OLD.status<>'cancelada' THEN
  INSERT INTO auditoria_cancelamento(id_venda,data_hora,id_funcionario,motivo) VALUES(NEW.id_venda,NEW.data_cancelamento,NEW.cancelada_por,NEW.motivo_cancelamento);
 END IF;
END$$
CREATE TRIGGER trg_movimento_validar BEFORE INSERT ON movimentacao_estoque FOR EACH ROW
BEGIN
 IF NEW.tipo IN ('entrada','ajuste_entrada','ajuste_saida') THEN
  IF TRIM(NEW.motivo)='' THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Movimentacao exige motivo'; END IF;
  IF NEW.tipo='ajuste_saida' AND NEW.quantidade>(SELECT estoque_atual FROM produto WHERE id_produto=NEW.id_produto) THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='Saldo insuficiente'; END IF;
 END IF;
END$$
CREATE TRIGGER trg_movimento_saldo AFTER INSERT ON movimentacao_estoque FOR EACH ROW
BEGIN
 IF NEW.tipo IN ('entrada','ajuste_entrada','ajuste_saida') THEN
  UPDATE produto SET estoque_atual=estoque_atual+IF(NEW.tipo='ajuste_saida',-NEW.quantidade,NEW.quantidade) WHERE id_produto=NEW.id_produto;
 END IF;
END$$
DELIMITER ;
