const searchInput = document.querySelector('#product-search');
const filterButtons = [...document.querySelectorAll('.filter')];
const cards = [...document.querySelectorAll('.product-card')];
const resultCount = document.querySelector('#result-count');
const emptyState = document.querySelector('#empty-state');
let activeFilter = 'todos';
function updateCatalog() {
  const term = searchInput.value.trim().toLocaleLowerCase('pt-BR');
  let visible = 0;
  cards.forEach(card => {
    const categoryMatches = activeFilter === 'todos' || card.dataset.category === activeFilter;
    const textMatches = (card.dataset.search + ' ' + card.textContent).toLocaleLowerCase('pt-BR').includes(term);
    const show = categoryMatches && textMatches;
    card.hidden = !show;
    if (show) visible++;
  });
  resultCount.textContent = visible;
  emptyState.hidden = visible !== 0;
}
searchInput.addEventListener('input', updateCatalog);
filterButtons.forEach(button => button.addEventListener('click', () => {
  activeFilter = button.dataset.filter;
  filterButtons.forEach(item => item.classList.toggle('active', item === button));
  updateCatalog();
}));
updateCatalog();
