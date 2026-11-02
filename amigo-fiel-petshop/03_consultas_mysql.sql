USE amigo_fiel_petshop;
-- 1. Animais e tutores
SELECT a.nome AS animal, a.especie, c.nome AS tutor FROM animal a JOIN cliente c ON c.id_cliente=a.id_cliente;
-- 2. Agenda por profissional
SELECT f.nome AS funcionario, a.inicio,a.fim,s.nome AS servico,an.nome AS animal,a.status FROM agendamento a JOIN funcionario f ON f.id_funcionario=a.id_funcionario JOIN servico s ON s.id_servico=a.id_servico JOIN animal an ON an.id_animal=a.id_animal ORDER BY a.inicio;
-- 3. Produtos abaixo do minimo
SELECT nome,estoque_atual,estoque_minimo FROM produto WHERE estoque_atual<=estoque_minimo;
-- 4. Vendas concluidas
SELECT v.id_venda,v.data_hora,v.valor_total,c.nome AS cliente FROM venda v LEFT JOIN cliente c ON c.id_cliente=v.id_cliente WHERE v.status='concluida';
-- 5. Historico do estoque
SELECT p.nome,m.tipo,m.quantidade,m.motivo,m.data_hora FROM movimentacao_estoque m JOIN produto p ON p.id_produto=m.id_produto ORDER BY m.id_movimentacao;
-- 6. Pagamentos por origem
SELECT id_pagamento,CASE WHEN id_venda IS NOT NULL THEN 'venda' ELSE 'atendimento' END AS origem,forma,valor,status FROM pagamento;
