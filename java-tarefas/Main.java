import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static final List<Tarefa> tarefas = new ArrayList<>();
    private static final Scanner scanner = new Scanner(System.in);

    private static class Tarefa {
        private final int id;
        private final String descricao;
        private boolean concluida;
        Tarefa(int id, String descricao) { this.id = id; this.descricao = descricao; this.concluida = false; }
        @Override public String toString() { return "[" + (concluida ? "x" : " ") + "] " + id + " - " + descricao; }
    }
    private static void listar() {
        if (tarefas.isEmpty()) { System.out.println("Nenhuma tarefa cadastrada."); return; }
        tarefas.forEach(System.out::println);
    }
    private static int lerInteiro(String mensagem) {
        while (true) { System.out.print(mensagem); String entrada = scanner.nextLine().trim(); try { return Integer.parseInt(entrada); } catch (NumberFormatException e) { System.out.println("Digite um número inteiro válido."); } }
    }
    public static void main(String[] args) {
        int proximoId = 1;
        while (true) {
            System.out.println("\n=== GERENCIADOR DE TAREFAS ===\n1. Adicionar\n2. Listar\n3. Concluir\n4. Remover\n0. Sair");
            int opcao = lerInteiro("Escolha: ");
            switch (opcao) {
                case 1 -> { System.out.print("Descrição: "); String descricao = scanner.nextLine().trim(); if (descricao.isBlank()) System.out.println("A descrição não pode ficar vazia."); else { tarefas.add(new Tarefa(proximoId++, descricao)); System.out.println("Tarefa adicionada."); } }
                case 2 -> listar();
                case 3 -> { listar(); if (!tarefas.isEmpty()) { int id = lerInteiro("ID para concluir: "); boolean achou = false; for (Tarefa t : tarefas) if (t.id == id) { t.concluida = true; achou = true; break; } System.out.println(achou ? "Tarefa concluída." : "ID não encontrado."); } }
                case 4 -> { listar(); if (!tarefas.isEmpty()) { int id = lerInteiro("ID para remover: "); boolean removida = tarefas.removeIf(t -> t.id == id); System.out.println(removida ? "Tarefa removida." : "ID não encontrado."); } }
                case 0 -> { System.out.println("Programa encerrado."); scanner.close(); return; }
                default -> System.out.println("Opção inválida.");
            }
        }
    }
}
