const express = require("express");
const routes = express.Router();

routes.post("/testePost", teste);

function teste(req, res){
    try{
        console.log(req.body)
        res.status(200).json({id: 134});
    } catch(e){
        console.log(e);
        res.status(500).json(e)
    }
}
module.exports = routes;

