const express = require('express');
const routes = require('./routes');
const cors = require('cors');

const port = process.env.PORT || 3000;

const app = express();

app.use(express.json());
app.use(routes);
app.use(cors());

app.listen(port, () => {
  console.log("Listening on port: " + port);
});
