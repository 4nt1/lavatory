var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
app.use(express.static('public'));

app.get('/', function(req, res){
  res.sendFile('index.html', { root: __dirname });
});

app.get('/on', function(req, res){
  io.emit('bulb-on', { for: 'everyone' });
  res.json({response: 'true'});
});

app.get('/off', function(req, res){
  io.emit('bulb-off', { for: 'everyone' });
  res.json({response: 'true'});
});

io.on('connection', function(socket){

});

http.listen(3000, function(){
  console.log('listening on *:3000');
});