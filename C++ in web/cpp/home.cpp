#include <iostream>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

std::vector<string> fetchArray(string getString)
{
      vector <string> keypairs; 
      
       stringstream temp1(getString);

       string intermediate; 
         
       while(getline(temp1, intermediate, ';')) 
       {
         stringstream temp2(intermediate);
         string seperator;
         while(getline(temp2, seperator, '=')) 
         {
            keypairs.push_back(seperator);
         }
       }   
      return keypairs;
}

int findIndex(std::vector<string> v, string keyword)
{
  for (int i = 0; i < v.size(); i++)
  {
    if(v[i] == keyword)
    { 
      return i;
    }
  }
  return  -1;
}


int main ()
{
  vector <string> getString = fetchArray((string)getenv("QUERY_STRING"));
  if(getString.empty())
  {
	cout << "Location: http://localhost/login.cgi\n\n";
	return 0;
  }
  if(findIndex(fetchArray(getenv("HTTP_COOKIE")), "user") == -1)
  {
    cout << "Location: http://localhost/login.cgi\n\n";
  }
  else
  {
  	cout << "Content-type: text/html\n\n";

	cout << "<html>\n";
	cout << "<head>\n";
	cout << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
	cout << "<title>Home</title>\n";
	cout << "<meta charset=\"utf-8\">\n";
	cout << "  <link href=\"https://fonts.googleapis.com/css?family=PT+Sans|Roboto+Condensed&display=swap\" rel=\"stylesheet\">\n";
    cout << "  <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n";
	cout << "</head>\n";
	cout << "<body class=\"canvas-body\">\n";
	cout << "<canvas>\n";
	cout << "</canvas>\n";
	cout << "<p class=\"title\">Welcome.......</p>\n";
	cout << "</body>\n";
	cout << "</html>\n";
	cout << "<script type=\"text/javascript\">\n";
	cout << "const canvas = document.querySelector('canvas');\n";
	cout << "const c = canvas.getContext('2d');\n";
	cout << "canvas.width = innerWidth;\n";
	cout << "canvas.height = innerHeight;\n";
	cout << "var mouse =\n";
	cout << "{\n";
	cout << "x: innerWidth / 2,\n";
	cout << "y: innerHeight / 2 \n";
	cout << "};\n";
	cout << "var colors =\n";
	cout << "[\n";
	cout << "'#2185C5',\n";
	cout << "'#7ECEFD',\n";
	cout << "'#FFF6E5',\n";
	cout << "'#FF7F66'\n";
	cout << "];\n";
	cout << "addEventListener(\"mousemove\", function(event)\n";
	cout << "{\n";
	cout << "mouse.x = event.clientX;\n";
	cout << "mouse.y = event.clientY;\n";
	cout << "});\n";
	cout << "addEventListener(\"resize\", function()\n";
	cout << "{\n";
	cout << "canvas.width = innerWidth;	\n";
	cout << "canvas.height = innerHeight;\n";
	cout << "});\n";
	cout << "function randomIntFromRange(min,max)\n";
	cout << "{\n";
	cout << "return Math.floor(Math.random() * (max - min + 1) + min);\n";
	cout << "}\n";
	cout << "function randomColor(colors)\n";
	cout << "{\n";
	cout << "return colors[Math.floor(Math.random() * colors.length)];\n";
	cout << "}\n";
	cout << "function getDistance(x1, y1, x2, y2)\n";
	cout << "{\n";
	cout << "let xDistance = x2 - x1;\n";
	cout << "let yDistance = y2 - y1;\n";
	cout << "return Math.sqrt(Math.pow(xDistance, 2) + Math.pow(yDistance, 2));\n";
	cout << "}\n";
	cout << "function findGetParameter(parameterName)\n";
	cout << "{\n";
	cout << "var result = null, tmp = [];\n";
	cout << "location.search\n";
	cout << ".substr(1)\n";
	cout << ".split(\"&\")\n";
	cout << ".forEach(function (item)\n";
	cout << "{\n";
	cout << "tmp = item.split(\"=\");\n";
	cout << "if (tmp[0] === parameterName) result = decodeURIComponent(tmp[1]);\n";
	cout << "});\n";
	cout << "return result;\n";
	cout << "}\n";
	cout << "function Bar(x, y, dx, dy, radius, color)\n";
	cout << "{\n";
	cout << "this.x = x;\n";
	cout << "this.y = y;\n";
	cout << "this.width = 100;\n";
	cout << "this.height = 50;\n";
	cout << "this.dy = 4;\n";
	cout << "this.draw = function()\n";
	cout << "{\n";
	cout << "c.beginPath();\n";
	cout << "c.rect(this.x, this.y, this.width, this.height);\n";
	cout << "c.fillStyle = '#72b5b7';\n";
	cout << "c.fill();\n";
	cout << "c.closePath();\n";
	cout << "c.beginPath();\n";
	cout << "c.rect(this.x-4, 46, this.width+8, canvas.height-92);\n";
	cout << "c.stroke();\n";
	cout << "c.closePath();\n";
	cout << "}\n";
	cout << "this.update = function()\n";
	cout << "{\n";
	cout << "if(this.y > 50)\n";
	cout << "{\n";
	cout << "this.height += this.dy;\n";
	cout << "this.y -= this.dy;\n";
	cout << "this.dy -= 0.02;\n";
	cout << "if(this.dy < -3)\n";
	cout << "{\n";
	cout << "this.dy += 6.5;\n";
	cout << "}\n";
	cout << "}\n";
	cout << "else if(window.v != \"done\")\n";
	cout << "{\n";
	cout << "document.querySelector('p').textContent = 'Your testosterone is full now, ' + findGetParameter(\"user\");\n";
	cout << "document.querySelector('p').style.color = '#1AA15F';\n";
	cout << "window.v = 'done';\n";
	cout << "}\n";
	cout << "this.draw();\n";
	cout << "}\n";
	cout << "}\n";
	cout << "let bar;\n";
	cout << "function init()\n";
	cout << "{\n";
	cout << "document.querySelector('p').textContent = 'Filling your testosterone now, ' + findGetParameter(\"user\") + \"......\";\n";
	cout << "let x = canvas.width/2-50;\n";
	cout << "let y = canvas.height-100;\n";
	cout << "bar = new Bar(x, y)\n";
	cout << "}\n";
	cout << "function animate()\n";
	cout << "{\n";
	cout << "requestAnimationFrame(animate);\n";
	cout << "c.clearRect(0, 0, innerWidth, innerHeight);\n";
	cout << "bar.update();\n";
	cout << "}\n";
	cout << "init();\n";
	cout << "animate();\n";
	cout << "</script>\n";
  }
  return 0;
}