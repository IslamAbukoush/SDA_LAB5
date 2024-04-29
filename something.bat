<!-- :
    @echo off
    mshta.exe "%~f0"
    exit /b %errorlevel%
-->

<html>
<head>
<link rel="shortcut icon" href="favicon.ico" type="image/icon">
</head>

<title>app</title>
<style>
* {
  font-family: sans-serif;
}
button {
  width: 300px;
  margin: 2px;
}

textarea {
  width: 500px;
  height: 200px;
  padding: 10px;
}
</style>
<body style='background-color: cyan'>
  <center>
  <h1>input:</h1>
  <textarea type="text" id=str></textarea>
  <div><br>
    <button onclick="w()">write to input.txt</button><br>
    <button onclick="execute('s')">split</button><br>
    <button onclick="execute('l2')">length of second sentence</button><br>
    <button onclick="execute('ns')">number of sentences</button><br>
    <button onclick="execute('out')">save to output.txt</button><br>
  </div>
  <h1>result:</h1>
  <div id=out></div>
  </center>
</body>
<script>
var WShell = new ActiveXObject('WScript.Shell');
function w() {
var res = str.value;
for(var i = 0; i < res.length; i++) {
  if(res[i] === '"') res[i] = '\\\"';
  if(res[i] === "'") res[i] = "\\\'";
}
var cmd = "./main w \"" + res + "\"";
var WShellExec = WShell.Exec(cmd);
var WShellResult = WShellExec.StdOut.ReadAll();
out.innerText = WShellResult;
}
function execute(s) {
  var cmd = './main ' + s;
  var WShellExec = WShell.Exec(cmd);
  var WShellResult = WShellExec.StdOut.ReadAll();
  out.innerText = WShellResult;
}
</script>
</html>
