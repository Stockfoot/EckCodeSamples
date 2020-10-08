//Root of the page which is in the div element on all_budgets.html
var page = document.getElementById('root');

//Get all the data from the currently logged in user
var request = new XMLHttpRequest();
request.open('GET', 'https://cs361group1.appspot.com/budgets', true);

request.onload = function () 
{
  
  // Begin accessing JSON data here
  var data = JSON.parse(this.response);
  console.log(data);
  if (request.status >= 200 && request.status < 400) 
  {
	  var list = document.createElement("ol");
	  var node;
	  var a;
	  var budget;
	  
	  for(var i = 0; i < data.length; i++)
	  {
		node = document.createElement("li");
		a = document.createElement('a');
		budget = document.createTextNode(data[i].name);
		a.appendChild(budget);
		a.title = data[i].name;
		a.href = "/update_budgets.html?name=" + data[i].name;
		node.appendChild(a);
		list.appendChild(node);
	  }
	  
	  page.appendChild(list);
  }

  else
  {
    const errorMessage = document.createElement('marquee');
    errorMessage.textContent = `Gah, it's not working!`;
    app.appendChild(errorMessage);
  }
}

request.send();