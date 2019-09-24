#ifndef HTML_DATA_h
#define HTML_DATA_h

#include <avr/pgmspace.h>

const char indexPage[] PROGMEM ="<!DOCTYPE html>\n\
<html lang=\"en\">\n\
\n\
<head>\n\
  <title>NX Server</title>\n\
  <meta charset=\"utf-8\">\n\
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
  <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">\n\
</head>\n\
\n\
<body>\n\
\n\
  <nav class=\"navbar navbar-dark sticky-top bg-dark flex-md-nowrap p-0\">\n\
    <a class=\"navbar-brand col-sm-3 col-md-2 mr-0\" href=\"#\">NX Server</a>\n\
  </nav>\n\
\n\
  <div class=\"container-fluid\">\n\
    <div class=\"row\">\n\
\n\
      <nav class=\"col-md-2 d-none d-md-block bg-light sidebar\">\n\
        <div class=\"sidebar-sticky\">\n\
          <ul class=\"nav flex-column\">\n\
            <li class=\"nav-item\">\n\
              <a class=\"nav-link\" href=\"/status\">\n\
                Status\n\
              </a>\n\
            </li>\n\
            <li class=\"nav-item\">\n\
              <a class=\"nav-link\" href=\"/config\">\n\
                Configuration\n\
              </a>\n\
            </li>\n\
          </ul>\n\
        </div>\n\
      </nav>\n\
\n\
      <main role=\"main\" class=\"col-md-9 ml-sm-auto col-lg-10 pt-3 px-4\">\n\
        <div class=\"d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom\">\n\
          <h1 class=\"h2\">Status</h1>\n\
        </div>\n\
      </main>\n\
    </div>\n\
  </div>\n\
\n\
</body>\n\
\n\
</html>\0";

const char statusPage[] PROGMEM = "<!DOCTYPE html>\n\
<html>\n\
\n\
<head>\n\
    <meta charset='utf-8'>\n\
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>\n\
    <title>NX Server Status Page</title>\n\
    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">\n\
    <meta name='viewport' content='width=device-width, initial-scale=1'>\n\
</head>\n\
\n\
<body onload=\"onLoaded()\">\n\
\n\
    <script>\n\
        function onLoaded() {\n\
            const Http = new XMLHttpRequest();\n\
            const url = 'http://192.168.4.1/api/getStatus';\n\
            Http.open(\"GET\", url);\n\
            Http.send();\n\
\n\
            Http.onreadystatechange = function () {\n\
                if (this.readyState == 4 && this.status == 200) {\n\
                    var obj = JSON.parse(Http.responseText);\n\
                    var ip = document.getElementById(\"ip\").innerHTML = obj.ip;\n\
                    var apIp = document.getElementById(\"apIp\").innerHTML = obj.apIp;\n\
                    var ssid = document.getElementById(\"ssid\").innerHTML = obj.ssid == \"\" ? \"(Unset)\" : obj.ssid;\n\
                    document.getElementById(\"opMode\").innerHTML = ip == apIp ? \"Connected Server\" : \"Isolated Access Point\";\n\
                }\n\
            }\n\
        }\n\
    </script>\n\
\n\
    <main role=\"main\" class=\"col-md-9 ml-sm-auto col-lg-10 pt-3 px-4\">\n\
        <div class=\"d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pb-2 mb-3 border-bottom\">\n\
            <h1 class=\"h2\">Status</h1>\n\
        </div>\n\
\n\
        <div class=\"col-md-6 mb-3\">\n\
            <label for=\"ssid\"><strong>Connected SSID:</strong></label>\n\
            <label id=\"ssid\"></label>\n\
        </div>\n\
        <div class=\"col-md-6 mb-3\">\n\
            <label for=\"ip\"><strong>Local IP:</strong></label>\n\
            <label id=\"ip\"></label>\n\
        </div>\n\
        <div class=\"col-md-6 mb-3\">\n\
            <label for=\"apIp\"><strong>Soft Access Point IP:</strong></label>\n\
            <label id=\"apIp\"></label>\n\
        </div>\n\
        <div class=\"col-md-6 mb-3\">\n\
            <label for=\"opMode\"><strong>Operating Mode:</strong></label>\n\
            <label id=\"opMode\"></label>\n\
        </div>\n\
\n\
    </main>\n\
\n\
\n\
\n\
</body>\n\
\n\
</html>\0";

const char configPage[] PROGMEM = "<!DOCTYPE html>\n\
<html>\n\
\n\
<head>\n\
    <meta charset='utf-8'>\n\
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>\n\
    <title>NX Server Configuration Page</title>\n\
    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">\n\
    <meta name='viewport' content='width=device-width, initial-scale=1'>\n\
\n\
    <style>\n\
        li:hover.hover {\n\
            background: darkcyan;\n\
            transition: 0.2s linear;\n\
        }\n\
\n\
        li:not(:hover).hover {\n\
            transition: 0.2s linear;\n\
        }\n\
    </style>\n\
</head>\n\
\n\
<body>\n\
\n\
    <script>\n\
        function refreshWLAN() {\n\
            const Http = new XMLHttpRequest();\n\
            const url = 'http://192.168.4.1/api/getWLANNetworks';\n\
            Http.open(\"GET\", url);\n\
            Http.send();\n\
            const loadingLabel = document.getElementById(\"loading\");\n\
            loadingLabel.hidden = false;\n\
\n\
            Http.onreadystatechange = function () {\n\
                if (this.readyState == 4 && this.status == 200) {\n\
                    loadingLabel.hidden = true;\n\
                    var obj = JSON.parse(Http.responseText);\n\
\n\
                    var ul = document.getElementsByTagName(\"ul\");\n\
                    for (var i = 0; i < obj.networks.length; i++) {\n\
                        let network = obj.networks[i];\n\
\n\
                        let listItem = document.createElement(\"li\");\n\
                        listItem.classList.add(\"mb-2\", \"border\", \"shadow-sm\", \"p-2\", \"hover\");\n\
\n\
                        let wrapper = document.createElement(\"div\");\n\
                        wrapper.classList.add(\"row\", \"pr-4\", \"pl-4\");\n\
\n\
                        let label = document.createElement(\"label\");\n\
                        label.innerText = network;\n\
                        wrapper.appendChild(label);\n\
\n\
                        let button = document.createElement(\"button\");\n\
                        button.classList.add(\"btn\", \"btn-sm\", \"btn-dark\", \"ml-auto\");\n\
                        button.textContent = \"Select\";\n\
                        button.addEventListener(\"click\", function () {\n\
                            var ssidField = document.getElementById(\"ssid\");\n\
                            if (ssidField) {\n\
                                ssidField.value = network;\n\
                            }\n\
                        });\n\
\n\
                        wrapper.appendChild(button);\n\
                        listItem.appendChild(wrapper);\n\
                        ul[0].appendChild(listItem);\n\
                    }\n\
                }\n\
            }\n\
        }\n\
    </script>\n\
\n\
    <main role=\"main\" class=\"col-md-9 ml-sm-auto col-lg-10 pt-3 px-4\">\n\
        <div class=\"row\">\n\
            <div class=\"col-lg-5\">\n\
                <form action=\"/api/configureServer\" method=\"POST\">\n\
                    <div class=\"mb-3\">\n\
                        <label for=\"ssid\">SSID Name:</label>\n\
                        <input name=\"ssid\" required type=\"text\" class=\"form-control\" id=\"ssid\"\n\
                            placeholder=\"My Network Name\">\n\
                    </div>\n\
                    <div class=\"mb-3\">\n\
                        <label for=\"pass\">Password</label>\n\
                        <input name=\"pass\" required type=\"text\" class=\"form-control\" id=\"pass\"\n\
                            placeholder=\"My Network Password Name\">\n\
                    </div>\n\
                    <br>\n\
                    <button class=\"btn btn-primary btn-lg col-3\" type=\"submit\">Submit</button>\n\
                </form>\n\
            </div>\n\
            <div class=\"col-lg-5\">\n\
                <div style=\"height:500px;border:1px solid #ccc;overflow:auto;\">\n\
                    <div style=\"border-radius: 0\" class=\"shadow-sm alert alert-dark row\">\n\
                        <div class=\"col-10\">\n\
                            <h4>WLAN Browser</h4>\n\
                        </div>\n\
                        <div>\n\
                            <button onclick=\"refreshWLAN()\" class=\"btn btn-primary\">Refresh</button>\n\
                        </div>\n\
                    </div>\n\
                    <h2 hidden id=\"loading\">\n\
                        Loading.....\n\
                    </h2>\n\
                    <ul class=\"container\" style=\"list-style-type:none\" id=\"wifi-list\">\n\
                        \n\
                    </ul>\n\
                </div>\n\
            </div>\n\
        </div>\n\
    </main>\n\
\n\
</body>\n\
\n\
</html>\0";

const char styles[] PROGMEM = ".btn-primary {\n\
    color: brown;\n\
}\0";

#endif