const toggle = document.querySelector('#theme-toggle');
const savedTheme = localStorage.getItem('portfolio-theme');
if (savedTheme === 'dark') document.body.classList.add('dark');
function updateLabel(){toggle.textContent = document.body.classList.contains('dark') ? '☀ Tema claro' : '☾ Tema escuro';}
toggle.addEventListener('click', () => {
  document.body.classList.toggle('dark');
  localStorage.setItem('portfolio-theme', document.body.classList.contains('dark') ? 'dark' : 'light');
  updateLabel();
});
updateLabel();
