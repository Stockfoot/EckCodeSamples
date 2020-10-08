//Root of the page which is in the div element on update_goals.html
var page = document.getElementById('root');


//Create DOM form
var form1 = document.createElement('form');
    form1.setAttribute('id', "form1");
    form1.setAttribute("method", "GET");
    form1.setAttribute("action", "/updateGoal");

    //DOM input for Goal Name
    var div1 = document.createElement('div');
      div1.setAttribute("class", "form-group");
    var div2 = document.createElement('div');
      div2.setAttribute("class", "form-row");
    var div3 = document.createElement('div');
      div3.setAttribute("class", "form-label-group");
      div3.innerHTML = "Goal Name";    
    var input3 = document.createElement("input");
      input3.setAttribute("id", "name");
      input3.setAttribute("name", "name");
      input3.setAttribute("class", "form-control");
      input3.setAttribute("type", "text");
      input3.setAttribute("required", "true");
      input3.setAttribute("autofocus", "autofocus");
	  
    var inputName = document.createElement("input");
      inputName.setAttribute("id", "orig_name");
      inputName.setAttribute("name", "orig_name");
      inputName.setAttribute("class", "form-control");
      inputName.setAttribute("type", "text");
      inputName.setAttribute("required", "true");
      inputName.setAttribute("autofocus", "autofocus");
	  inputName.setAttribute("type", "hidden");
	  
    //DOM input for Total Amount
    var div4 = document.createElement('div');
      div4.setAttribute("class", "form-group");
    var div5 = document.createElement('div');
      div5.setAttribute("class", "form-row");
    var div6 = document.createElement('div');
      div6.setAttribute("class", "form-label-group");
      div6.innerHTML = "Total Amount"; 
    var input1 = document.createElement("input");
      input1.setAttribute("id", "tamount");
      input1.setAttribute("name", "tamount");
      input1.setAttribute("class", "form-control");
      input1.setAttribute("type", "number");
      input1.setAttribute("required", "true");
      input1.setAttribute("autofocus", "autofocus");
  
    //DOM input for Start Date
    var div7 = document.createElement('div');
      div7.setAttribute("class", "form-group");
    var div8 = document.createElement('div');
      div8.setAttribute("class", "form-row");
    var div9 = document.createElement('div');
      div9.setAttribute("class", "form-label-group");
      div9.innerHTML = "Start Date"; 
    var input2 = document.createElement("input");
      input2.setAttribute("id", "startdate");
      input2.setAttribute("name", "startdate");
      input2.setAttribute("class", "form-control");
      input2.setAttribute("type", "date");
      input2.setAttribute("required", "true");
      input2.setAttribute("autofocus", "autofocus");

    //DOM input for Contribution Amount
    var div10 = document.createElement('div');
      div10.setAttribute("class", "form-group");
    var div11 = document.createElement('div');
      div11.setAttribute("class", "form-row");
    var div12 = document.createElement('div');
      div12.setAttribute("class", "form-label-group");
      div12.innerHTML = "Contribution Amount"; 
    var input6 = document.createElement("input");
      input6.setAttribute("id", "camount");
      input6.setAttribute("name", "camount");
      input6.setAttribute("type", "number");
      input6.setAttribute("class", "form-control");
      input6.setAttribute("required", "true");
      input6.setAttribute("autofocus", "autofocus");
    
    //DOM input for Contribution Frequency
    var div13 = document.createElement('div');
      div13.setAttribute("class", "form-group");
    var div14 = document.createElement('div');
      div14.setAttribute("class", "form-row");
    var div15 = document.createElement('div');
      div15.setAttribute("class", "form-label-group");
      div15.innerHTML = "Contribution Frequency"; 
    var input4 = document.createElement("select");
      input4.setAttribute("id", "cfrequency");
      input4.setAttribute("name", "cfrequency");
      input4.setAttribute("class", "form-control");
      input4.setAttribute("required", "true");
      input4.setAttribute("autofocus", "autofocus");
    var option1 = document.createElement("option");
      option1.text = "Weekly";
      option1.value = "Weekly";
    var option2 = document.createElement("option");
      option2.text = "Monthly";
      option2.value = "Monthly";

    //DOM input for Estimated Date To Goal
    var div16 = document.createElement('div');
      div16.setAttribute("class", "form-group");
    var div17 = document.createElement('div');
      div17.setAttribute("class", "form-row");
    var div18 = document.createElement('div');
      div18.setAttribute("class", "form-label-group");
      div18.innerHTML = "Estimate Date To Goal"; 
    var input5 = document.createElement("input");
      input5.setAttribute("id", "edr");
      input5.setAttribute("name", "edr");
      input5.setAttribute("class", "form-control");
      input5.setAttribute("type", "text");
      input5.setAttribute("autofocus", "autofocus");

/*
    //DOM input for goal_id (FOR TEST PURPOSES)
    var div31 = document.createElement('div');
      div31.setAttribute("class", "form-group");
    var div32 = document.createElement('div');
      div32.setAttribute("class", "form-row");
    var div33 = document.createElement('div');
      div33.setAttribute("class", "form-label-group");
      div33.innerHTML = "Goal ID"; 
    var input11 = document.createElement("input");
      input11.setAttribute("id", "goal_id");
      input11.setAttribute("name", "goal_id");
      input11.setAttribute("class", "form-control");
      input11.setAttribute("type", "text");
      input11.setAttribute("required", "true");
      input11.setAttribute("autofocus", "autofocus");
      input11.setAttribute("readonly", "true");
*/
  
    //DOM submit button
    var submit1 = document.createElement("input");
      submit1.setAttribute("type", "submit");
      submit1.setAttribute("value", "Update Goal");
    
//Append all the DOM elements to the page

//Goal Name
page.appendChild(form1);
  form1.appendChild(div1);
    div1.appendChild(div2);
      div2.appendChild(div3);
        div3.appendChild(input3);
		div3.appendChild(inputName);
  //Total Amount
  form1.appendChild(div4);
    div4.appendChild(div5);
      div5.appendChild(div6);
        div6.appendChild(input1);
  //Start Date
  form1.appendChild(div7);
    div7.appendChild(div8);
      div8.appendChild(div9);
        div9.appendChild(input2);
  //Contribution Amount
  form1.appendChild(div10);
    div10.appendChild(div11);
      div11.appendChild(div12);
        div12.appendChild(input6);
  //Contribution Frequency
  form1.appendChild(div13);
    div13.appendChild(div14);
      div14.appendChild(div15);
        div15.appendChild(input4);
          input4.appendChild(option1);
          input4.appendChild(option2);
  //Estimated Date To Goal
  form1.appendChild(div16);
    div16.appendChild(div17);
      div17.appendChild(div18);
        div18.appendChild(input5);
  //Goal ID for testing purposes
  /*
  form1.appendChild(div31);
    div31.appendChild(div32);
      div32.appendChild(div33);
        div33.appendChild(input11);
*/

  //Submit Button
  form1.appendChild(submit1);

//Parse query string to get goal name
//Source: https://stackoverflow.com/questions/901115/how-can-i-get-query-string-values-in-javascript
var urlParams;
(window.onpopstate = function () {
    var match,
        pl     = /\+/g,  // Regex for replacing addition symbol with a space
        search = /([^&=]+)=?([^&]*)/g,
        decode = function (s) { return decodeURIComponent(s.replace(pl, " ")); },
        query  = window.location.search.substring(1);

    urlParams = {};
    while (match = search.exec(query))
       urlParams[decode(match[1])] = decode(match[2]);
})();

//Get all the data from the currently logged in user
var request = new XMLHttpRequest();
request.open('GET', 'https://cs361group1.appspot.com/goal?name=' + urlParams["name"], true);

request.onload = function () 
{
  
  // Begin accessing JSON data here
  var data = JSON.parse(this.response);
  console.log(data);
  
  if (request.status >= 200 && request.status < 400) 
  {
      
      //Set the value of the fields in the html document with credentials from user
      input1.setAttribute("value", data.tamount);
      input2.setAttribute("value", data.startdate);
      input3.setAttribute("value", data.name);
      input4.setAttribute("value", data.cfrequency);
      input6.setAttribute("value", data.camount);
	  inputName.setAttribute("value", data.name);

  }

  else
  {
    const errorMessage = document.createElement('marquee');
    errorMessage.textContent = `Gah, it's not working!`;
    app.appendChild(errorMessage);
  }
}

request.send();
