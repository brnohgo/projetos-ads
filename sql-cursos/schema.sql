-- Banco demonstrativo para SQLite: cursos, alunos e matrículas.
PRAGMA foreign_keys = ON;
DROP TABLE IF EXISTS matriculas;
DROP TABLE IF EXISTS alunos;
DROP TABLE IF EXISTS cursos;
CREATE TABLE cursos (
    id INTEGER PRIMARY KEY,
    nome TEXT NOT NULL UNIQUE,
    carga_horaria INTEGER NOT NULL CHECK (carga_horaria > 0)
);
CREATE TABLE alunos (
    id INTEGER PRIMARY KEY,
    nome TEXT NOT NULL,
    email TEXT NOT NULL UNIQUE
);
CREATE TABLE matriculas (
    aluno_id INTEGER NOT NULL,
    curso_id INTEGER NOT NULL,
    data_matricula TEXT NOT NULL DEFAULT (date('now')),
    nota REAL CHECK (nota IS NULL OR (nota >= 0 AND nota <= 10)),
    situacao TEXT NOT NULL DEFAULT 'Em andamento' CHECK (situacao IN ('Em andamento','Aprovado','Reprovado','Trancado')),
    PRIMARY KEY (aluno_id, curso_id),
    FOREIGN KEY (aluno_id) REFERENCES alunos(id) ON DELETE CASCADE,
    FOREIGN KEY (curso_id) REFERENCES cursos(id) ON DELETE CASCADE
);
INSERT INTO cursos (id,nome,carga_horaria) VALUES
 (1,'Lógica de Programação',80),(2,'Banco de Dados',60),(3,'Desenvolvimento Web',80);
INSERT INTO alunos (id,nome,email) VALUES
 (1,'Ana Souza','ana@example.com'),(2,'Caio Lima','caio@example.com'),(3,'Marina Alves','marina@example.com');
INSERT INTO matriculas (aluno_id,curso_id,data_matricula,nota,situacao) VALUES
 (1,1,'2026-08-10',9.0,'Aprovado'),(1,2,'2026-08-10',8.5,'Em andamento'),
 (2,1,'2026-08-11',7.5,'Aprovado'),(2,3,'2026-08-11',NULL,'Em andamento'),
 (3,2,'2026-08-12',6.0,'Em andamento');

-- 1. Ver alunos matriculados em cada curso.
SELECT a.nome AS aluno, c.nome AS curso, m.situacao, m.nota
FROM matriculas m JOIN alunos a ON a.id=m.aluno_id JOIN cursos c ON c.id=m.curso_id
ORDER BY c.nome, a.nome;

-- 2. Quantidade de alunos por curso (inclui cursos sem matrícula).
SELECT c.nome AS curso, COUNT(m.aluno_id) AS total_alunos
FROM cursos c LEFT JOIN matriculas m ON m.curso_id=c.id
GROUP BY c.id, c.nome ORDER BY total_alunos DESC;

-- 3. Média das notas registradas por curso.
SELECT c.nome AS curso, ROUND(AVG(m.nota), 2) AS media_notas
FROM cursos c LEFT JOIN matriculas m ON m.curso_id=c.id
GROUP BY c.id, c.nome;
