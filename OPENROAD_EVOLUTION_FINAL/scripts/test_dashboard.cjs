// Exercise the offline dashboard's filters, sorting and pagination without a browser.
const fs = require('fs');
const vm = require('vm');
const path = require('path');
const root = path.resolve(process.argv[2]);
const html = fs.readFileSync(path.join(root, 'index.html'), 'utf8');
const script = html.match(/<script>([\s\S]*?)<\/script>/)[1];
const nodes = {};
function node(id) {
  if (!nodes[id]) nodes[id] = {value:'', innerHTML:'', textContent:'', listeners:{}, addEventListener(event, fn){this.listeners[event]=fn;}};
  return nodes[id];
}
node('candidate-sort').value = 'iteration';
node('source-rows').rows = [
  {textContent:'src/cts/src/Clustering_new.cpp production source'},
  {textContent:'src/rsz/src/policy/SetupLegacyBase_new.cc production source'},
  {textContent:'learning_evolution/tests/Graph.cpp tests / tooling'}
];
vm.runInNewContext(script, {document:{getElementById:node}, console}, {timeout:5000});
function check(condition, message){if(!condition)throw new Error(message);}
check((node('candidate-rows').innerHTML.match(/<tr>/g)||[]).length===50, 'first page should contain 50 rows');
const firstPage = node('candidate-rows').innerHTML;
node('next').onclick();
check(node('candidate-rows').innerHTML!==firstPage, 'next page must change rows');
node('previous').onclick();
check(node('candidate-rows').innerHTML===firstPage, 'previous page must restore rows');
node('candidate-sort').value='score';node('candidate-sort').listeners.input();
check(node('candidate-rows').innerHTML!==firstPage, 'score sorting should change ordering');
node('candidate-search').value='not-a-real-hash';node('candidate-search').listeners.input();
check(node('candidate-rows').innerHTML==='', 'unmatched search should contain no rows');
check(node('candidate-count').textContent.startsWith('0 matching'), 'empty query count');
node('source-search').value='Clustering';node('source-search').oninput();
check(node('source-rows').rows.filter(row=>!row.hidden).length===1, 'source path filtering');
console.log('PASS: dashboard JavaScript syntax, 50-row pagination, score sorting, candidate filtering and source filtering');
