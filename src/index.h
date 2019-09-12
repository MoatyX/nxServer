#ifndef INDEX_H
#define INDEX_H

char* indexPage = "<!DOCTYPE html>\n\
<html lang=\"en\">\n\
<head>\n\
  <title>NX Server</title>\n\
  <meta charset=\"utf-8\">\n\
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\
  <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">\n\
  <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js\"></script>\n\
  <script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\"></script>\n\
  <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\"></script>\n\
</head>\n\
<body>\n\
\n\
  <script type=\"text/javascript\">\n\
    var clicks = 0;\n\
    function onClick() {\n\
        clicks += 1;\n\
        document.getElementById(\"clicks\").innerHTML = clicks;\n\
    };\n\
    </script>\n\
    \n\
  <form action=\"/led\" method=\"POST\">\n\
    <button type=\"submit\" onclick=\"onClick()\" class=\"btn btn-primary\">Submit</button>\n\
    <p>Clicks: <a id=\"clicks\">0</a></p>\n\
  </form> \n\
\n\
</body>\n\
</html>";

#endif