const http = require('http');
const fs = require('fs');
const path = require('path');

const PORT = 8080;

const server = http.createServer((req, res) => {
  let urlPath = req.url;

  // Redirect root to /index.gmi
  if (urlPath === '/' || urlPath === '') {
    res.writeHead(301, { 'Location': '/index.gmi' });
    res.end();
    return;
  }

  // Redirect /fr/ to /fr/index.gmi
  if (urlPath === '/fr' || urlPath === '/fr/') {
    res.writeHead(301, { 'Location': '/fr/index.gmi' });
    res.end();
    return;
  }

  // Determine file path based on URL
  let filePath;
  if (urlPath.startsWith('/fr/')) {
    let page = urlPath.slice(4); // remove /fr/
    if (page.endsWith('.gmi')) {
      page = page.replace('.gmi', '.html');
    } else {
      page = page + '.html';
    }
    filePath = './html/fr/' + page;
  } else {
    if (urlPath.endsWith('.gmi')) {
      filePath = './html/' + urlPath.replace('.gmi', '.html');
    } else {
      filePath = './html/' + urlPath + '.html';
    }
  }

  fs.readFile(filePath, 'utf8', (err, content) => {
    if (err) {
      res.writeHead(404, { 'Content-Type': 'text/html' });
      res.end('<h1>404 Not Found</h1>');
    } else {
      res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
      res.end(content);
    }
  });
});

server.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}/`);
});
