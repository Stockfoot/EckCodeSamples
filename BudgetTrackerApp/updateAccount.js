//Root of the page which is in the div element on updateAccount.html
var page = document.getElementById('root');


//Create DOM form
var form1 = document.createElement('form');
    form1.setAttribute('id', "form1");
    form1.setAttribute("method", "GET");
    form1.setAttribute("action", "/updateAccount");

    //DOM input for username
    var div1 = document.createElement('div');
      div1.setAttribute("class", "form-group");
    var div2 = document.createElement('div');
      div2.setAttribute("class", "form-row");
    var div3 = document.createElement('div');
      div3.setAttribute("class", "form-label-group");
      div3.innerHTML = "Username";    
    var input3 = document.createElement("input");
      input3.setAttribute("id", "username");
      input3.setAttribute("name", "username");
      input3.setAttribute("class", "form-control");
      input3.setAttribute("type", "text");
      input3.setAttribute("required", "true");
      input3.setAttribute("autofocus", "autofocus");

    //DOM input for first_name
    var div4 = document.createElement('div');
      div4.setAttribute("class", "form-group");
    var div5 = document.createElement('div');
      div5.setAttribute("class", "form-row");
    var div6 = document.createElement('div');
      div6.setAttribute("class", "form-label-group");
      div6.innerHTML = "First Name"; 
    var input1 = document.createElement("input");
      input1.setAttribute("id", "first_name");
      input1.setAttribute("name", "first_name");
      input1.setAttribute("class", "form-control");
      input1.setAttribute("type", "text");
      input1.setAttribute("required", "true");
      input1.setAttribute("autofocus", "autofocus");
      input1.setAttribute("readonly", "true");
  
    //DOM input for last_name
    var div7 = document.createElement('div');
      div7.setAttribute("class", "form-group");
    var div8 = document.createElement('div');
      div8.setAttribute("class", "form-row");
    var div9 = document.createElement('div');
      div9.setAttribute("class", "form-label-group");
      div9.innerHTML = "Last Name"; 
    var input2 = document.createElement("input");
      input2.setAttribute("id", "last_name");
      input2.setAttribute("name", "last_name");
      input2.setAttribute("class", "form-control");
      input2.setAttribute("type", "text");
      input2.setAttribute("required", "true");
      input2.setAttribute("autofocus", "autofocus");
      input2.setAttribute("readonly", "true");

    //DOM input for email
    var div10 = document.createElement('div');
      div10.setAttribute("class", "form-group");
    var div11 = document.createElement('div');
      div11.setAttribute("class", "form-row");
    var div12 = document.createElement('div');
      div12.setAttribute("class", "form-label-group");
      div12.innerHTML = "Email"; 
    var input6 = document.createElement("input");
      input6.setAttribute("id", "email");
      input6.setAttribute("name", "email");
      input6.setAttribute("class", "form-control");
      input6.setAttribute("type", "text");
      input6.setAttribute("required", "true");
      input6.setAttribute("autofocus", "autofocus");
      input6.setAttribute("readonly", "true");
    
    //DOM input for age
    var div13 = document.createElement('div');
      div13.setAttribute("class", "form-group");
    var div14 = document.createElement('div');
      div14.setAttribute("class", "form-row");
    var div15 = document.createElement('div');
      div15.setAttribute("class", "form-label-group");
      div15.innerHTML = "Age"; 
    var input4 = document.createElement("input");
      input4.setAttribute("id", "age");
      input4.setAttribute("name", "age");
      input4.setAttribute("class", "form-control");
      input4.setAttribute("type", "text");
      input4.setAttribute("required", "true");
      input4.setAttribute("autofocus", "autofocus");
    
    //DOM input for zip
    var div16 = document.createElement('div');
      div16.setAttribute("class", "form-group");
    var div17 = document.createElement('div');
      div17.setAttribute("class", "form-row");
    var div18 = document.createElement('div');
      div18.setAttribute("class", "form-label-group");
      div18.innerHTML = "Zip"; 
    var input5 = document.createElement("input");
      input5.setAttribute("id", "zip");
      input5.setAttribute("name", "zip");
      input5.setAttribute("class", "form-control");
      input5.setAttribute("type", "text");
      input5.setAttribute("required", "true");
      input5.setAttribute("autofocus", "autofocus");

    //DOM input for user_id
    var div19 = document.createElement('div');
      div19.setAttribute("class", "form-group");
    var div20 = document.createElement('div');
      div20.setAttribute("class", "form-row");
    var div21 = document.createElement('div');
      div21.setAttribute("class", "form-label-group");
      div21.innerHTML = "User ID"; 
    var input7 = document.createElement("input");
      input7.setAttribute("id", "user_id");
      input7.setAttribute("name", "user_id");
      input7.setAttribute("class", "form-control");
      input7.setAttribute("type", "text");
      input7.setAttribute("required", "true");
      input7.setAttribute("autofocus", "autofocus");
      input7.setAttribute("readonly", "true");
  
    //DOM submit button
    var submit1 = document.createElement("input");
      submit1.setAttribute("type", "submit");
      submit1.setAttribute("value", "submit");
    
//Append all the DOM elements to the page
page.appendChild(form1);
  form1.appendChild(div1);
    div1.appendChild(div2);
      div2.appendChild(div3);
        div3.appendChild(input3);
  form1.appendChild(div4);
    div4.appendChild(div5);
      div5.appendChild(div6);
        div6.appendChild(input1);
  form1.appendChild(div7);
    div7.appendChild(div8);
      div8.appendChild(div9);
        div9.appendChild(input2);
  form1.appendChild(div10);
    div10.appendChild(div11);
      div11.appendChild(div12);
        div12.appendChild(input6);
  form1.appendChild(div13);
    div13.appendChild(div14);
      div14.appendChild(div15);
        div15.appendChild(input4);
  form1.appendChild(div16);
    div16.appendChild(div17);
      div17.appendChild(div18);
        div18.appendChild(input5);
  form1.appendChild(div19);
    div19.appendChild(div20);
      div20.appendChild(div21);
        div21.appendChild(input7);
  form1.appendChild(submit1);

//Get all the data from the currently logged in user
var request = new XMLHttpRequest();
request.open('GET', 'https://cs361group1.appspot.com/user', true);

request.onload = function () 
{
  
  // Begin accessing JSON data here
  var data = JSON.parse(this.response);
  console.log(data);
  if (request.status >= 200 && request.status < 400) 
  {
      
      //Set the value of the fields in the html document with credentials from user
      input1.setAttribute("value", data.first_name);
      input2.setAttribute("value", data.last_name);
      input3.setAttribute("value", data.username);
      input4.setAttribute("value", data.age);
      input5.setAttribute("value", data.zip);
      input6.setAttribute("value", data.email);
      input7.setAttribute("value", data.user_id);

  }

  else
  {
    const errorMessage = document.createElement('marquee');
    errorMessage.textContent = `Gah, it's not working!`;
    app.appendChild(errorMessage);
  }
}

request.send();