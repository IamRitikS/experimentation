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
  if(getenv("HTTP_COOKIE"))
  {
      std::vector<string> v = fetchArray(getenv("HTTP_COOKIE"));
      int index = findIndex(v, "user");
      if(index != -1)
      {
        cout << "Location: http://localhost/curd.cgi?action=cookie-resolve&user=" << v[index+1] << "\n\n";
      }
  }
  else
  {
    cout << "Content-type: text/html\n\n";
    cout << "<html>";
    cout << "<head>";
    cout << "  <link href=\"https://fonts.googleapis.com/css?family=PT+Sans|Roboto+Condensed&display=swap\" rel=\"stylesheet\">";
    cout << "  <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">";
    cout << "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    cout << "  <title>Signup</title>";
    cout << "</head>";
    cout << "<body>";
    cout << "  <div class=\"centered\">";
    cout << "    <h1>Sign Up with us</h1>";
    cout << "    <h3>Not registered with us yet? Pfft. You know we distribute testosterone, right??</h3>";
    cout << "    <h4>Not convinced yet? I'll cut you a deal. It's available for free</h4>";
    cout << "    <form action=\"curd.cgi?action=registration\" method=\"post\">";
    cout << "      <input type=\"text\" name=\"firstName\" placeholder=\"First Name\">";
    cout << "      <input type=\"text\" name=\"lastName\" placeholder=\"Last Name\">";
    cout << "      <input type=\"email\" name=\"email\" placeholder=\"Give us your email\">";
    cout << "      <input type=\"Password\" name=\"password\" placeholder=\"Password too\">";
    cout << "      <br>";
    cout << "      <button type=\"submit\">Submit</button>";
    cout << "      <p>";
    cout << "        Already registered? Log in right now before it's too late.";
    cout << "        <br>";
    cout << "        <a href=\"login.cgi\">Login Now</a>";
    cout << "      </p>";
    cout << "    </form>";
    cout << "  </div>";
    cout << "</body>";
    cout << "</html>";
  }
  return 0;
}