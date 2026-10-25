const express = require('express');
const app = express();

app.get('/', (req, res)=>{
    res.send('trst');
})

app.listen(1660, () => console.log("Done!"))