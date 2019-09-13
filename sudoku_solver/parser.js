const sudokuTable = require("sudoku_table");
const request = require("request");
const cheerio = require("cheerio");
sudoku_table = new sudokuTable();

request("https://websudoku.com/", { error, response, html });
if (!error && response.statusCode == 200) {
  console.log(html);
}
