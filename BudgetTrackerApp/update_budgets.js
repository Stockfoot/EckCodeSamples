//Root of the page which is in the div element on update_budgets.html
var page = document.getElementById('root');


//Create DOM form
var form1 = document.createElement('form');
    form1.setAttribute('id', "form1");
    form1.setAttribute("method", "GET");
    form1.setAttribute("action", "/updateBudget");

    //DOM input for Budget Name
    var div1 = document.createElement('div');
      div1.setAttribute("class", "form-group");
    var div2 = document.createElement('div');
      div2.setAttribute("class", "form-row");
    var div3 = document.createElement('div');
      div3.setAttribute("class", "form-label-group");
      div3.innerHTML = "Budget Name";    
    var input3 = document.createElement("input");
      input3.setAttribute("id", "budgetName");
      input3.setAttribute("name", "budgetName");
      input3.setAttribute("class", "form-control");
      input3.setAttribute("type", "text");
      input3.setAttribute("required", "true");
      input3.setAttribute("autofocus", "autofocus");

    //DOM input for budgetMonth
    var div4 = document.createElement('div');
      div4.setAttribute("class", "form-group");
    var div5 = document.createElement('div');
      div5.setAttribute("class", "form-row");
    var div6 = document.createElement('div');
      div6.setAttribute("class", "form-label-group");
      div6.innerHTML = "Budget Month"; 
    var input1 = document.createElement("select");
      input1.setAttribute("id", "budgetMonth");
      input1.setAttribute("name", "budgetMonth");
      input1.setAttribute("class", "form-control");
      input1.setAttribute("required", "true");
      input1.setAttribute("autofocus", "autofocus");
    var option1 = document.createElement("option");
      option1.text = "January";
      option1.value = "January";
    var option2 = document.createElement("option");
      option2.text = "February";
      option2.value = "February";
    var option3 = document.createElement("option");
      option3.text = "March";
      option3.value = "March";
    var option4 = document.createElement("option");
      option4.text = "April";
      option4.value = "April";
    var option5 = document.createElement("option");
      option5.text = "May";
      option5.value = "May";
    var option6 = document.createElement("option");
      option6.text = "June";
      option6.value = "June";
    var option7 = document.createElement("option");
      option7.text = "July";
      option7.value = "July";
    var option8 = document.createElement("option");
      option8.text = "August";
      option8.value = "August";
    var option9 = document.createElement("option");
      option9.text = "September";
      option9.value = "September";
    var option10 = document.createElement("option");
      option10.text = "October";
      option10.value = "October";
    var option11 = document.createElement("option");
      option11.text = "November";
      option11.value = "November";
    var option12 = document.createElement("option");
      option12.text = "December";
      option12.value = "December";
 
  
    //DOM input for totalBudget
    var div7 = document.createElement('div');
      div7.setAttribute("class", "form-group");
    var div8 = document.createElement('div');
      div8.setAttribute("class", "form-row");
    var div9 = document.createElement('div');
      div9.setAttribute("class", "form-label-group");
      div9.innerHTML = "Total Budget"; 
    var input2 = document.createElement("input");
      input2.setAttribute("id", "totalBudget");
      input2.setAttribute("name", "totalBudget");
      input2.setAttribute("class", "form-control");
      input2.setAttribute("type", "number");
      input2.setAttribute("required", "true");
      input2.setAttribute("autofocus", "autofocus");

    //DOM input for budgetNotToExceed
    var div10 = document.createElement('div');
      div10.setAttribute("class", "form-group");
    var div11 = document.createElement('div');
      div11.setAttribute("class", "form-row");
    var div12 = document.createElement('div');
      div12.setAttribute("class", "form-label-group");
      div12.innerHTML = "Budget Not To Exceed"; 
    var input6 = document.createElement("input");
      input6.setAttribute("id", "budgetNotToExceed");
      input6.setAttribute("name", "budgetNotToExceed");
      input6.setAttribute("type", "number");
      input6.setAttribute("class", "form-control");
      input6.setAttribute("required", "true");
      input6.setAttribute("autofocus", "autofocus");
    
    //DOM input for budgetCategory1
    var div13 = document.createElement('div');
      div13.setAttribute("class", "form-group");
    var div14 = document.createElement('div');
      div14.setAttribute("class", "form-row");
    var div15 = document.createElement('div');
      div15.setAttribute("class", "form-label-group");
      div15.innerHTML = "Budget Category 1"; 
    var input4 = document.createElement("select");
      input4.setAttribute("id", "budgetCategory1");
      input4.setAttribute("name", "budgetCategory1");
      input4.setAttribute("class", "form-control");
      input4.setAttribute("required", "true");
      input4.setAttribute("autofocus", "autofocus");

    //Budget Category Options 1
    var bcoption1 = document.createElement("option");
      bcoption1.text = "Grocery";
      bcoption1.value = "Grocery";
    var bcoption2 = document.createElement("option");
      bcoption2.text = "Restaurant";
      bcoption2.value = "Restaurant";
    var bcoption3 = document.createElement("option");
      bcoption3.text = "Retail";
      bcoption3.value = "Retail";
  
    //DOM input for targetBudgetCategory1
    var div16 = document.createElement('div');
      div16.setAttribute("class", "form-group");
    var div17 = document.createElement('div');
      div17.setAttribute("class", "form-row");
    var div18 = document.createElement('div');
      div18.setAttribute("class", "form-label-group");
      div18.innerHTML = "Target Budget Category 1"; 
    var input5 = document.createElement("input");
      input5.setAttribute("id", "targetBudgetCategory1");
      input5.setAttribute("name", "targetBudgetCategory1");
      input5.setAttribute("class", "form-control");
      input5.setAttribute("type", "number");
      input5.setAttribute("required", "true");
      input5.setAttribute("autofocus", "autofocus");

    //DOM input for budgetCategory2
    var div19 = document.createElement('div');
      div19.setAttribute("class", "form-group");
    var div20 = document.createElement('div');
      div20.setAttribute("class", "form-row");
    var div21 = document.createElement('div');
      div21.setAttribute("class", "form-label-group");
      div21.innerHTML = "Budget Category 2"; 
    var input7 = document.createElement("select");
      input7.setAttribute("id", "budgetCategory2");
      input7.setAttribute("name", "budgetCategory2");
      input7.setAttribute("class", "form-control");
      input7.setAttribute("required", "true");
      input7.setAttribute("autofocus", "autofocus");

    //Budget Category Options 2
    var bcoption4 = document.createElement("option");
      bcoption4.text = "Grocery";
      bcoption4.value = "Grocery";
    var bcoption5 = document.createElement("option");
      bcoption5.text = "Restaurant";
      bcoption5.value = "Restaurant";
    var bcoption6 = document.createElement("option");
      bcoption6.text = "Retail";
      bcoption6.value = "Retail";

    //DOM input for targetBudgetCategory2
    var div22 = document.createElement('div');
      div22.setAttribute("class", "form-group");
    var div23 = document.createElement('div');
      div23.setAttribute("class", "form-row");
    var div24 = document.createElement('div');
      div24.setAttribute("class", "form-label-group");
      div24.innerHTML = "Target Budget Category 2"; 
    var input8 = document.createElement("input");
      input8.setAttribute("id", "targetBudgetCategory2");
      input8.setAttribute("name", "targetBudgetCategory2");
      input8.setAttribute("class", "form-control");
      input8.setAttribute("type", "number");
      input8.setAttribute("required", "true");
      input8.setAttribute("autofocus", "autofocus");

    //DOM input for budgetCategory3
    var div25 = document.createElement('div');
      div25.setAttribute("class", "form-group");
    var div26 = document.createElement('div');
      div26.setAttribute("class", "form-row");
    var div27 = document.createElement('div');
      div27.setAttribute("class", "form-label-group");
      div27.innerHTML = "Budget Category 3"; 
    var input9 = document.createElement("select");
      input9.setAttribute("id", "budgetCategory3");
      input9.setAttribute("name", "budgetCategory3");
      input9.setAttribute("class", "form-control");
      input9.setAttribute("required", "true");
      input9.setAttribute("autofocus", "autofocus");

    //Budget Category Options 3
    var bcoption7 = document.createElement("option");
      bcoption7.text = "Grocery";
      bcoption7.value = "Grocery";
    var bcoption8 = document.createElement("option");
      bcoption8.text = "Restaurant";
      bcoption8.value = "Restaurant";
    var bcoption9 = document.createElement("option");
      bcoption9.text = "Retail";
      bcoption9.value = "Retail";

    //DOM input for targetBudgetCategory3
    var div28 = document.createElement('div');
      div28.setAttribute("class", "form-group");
    var div29 = document.createElement('div');
      div29.setAttribute("class", "form-row");
    var div30 = document.createElement('div');
      div30.setAttribute("class", "form-label-group");
      div30.innerHTML = "Target Budget Category 3"; 
    var input10 = document.createElement("input");
      input10.setAttribute("id", "targetBudgetCategory3");
      input10.setAttribute("name", "targetBudgetCategory3");
      input10.setAttribute("class", "form-control");
      input10.setAttribute("type", "number");
      input10.setAttribute("required", "true");
      input10.setAttribute("autofocus", "autofocus");

    //DOM input for budget_id (FOR TEST PURPOSES)
    var div31 = document.createElement('div');
      div31.setAttribute("class", "form-group");
    var div32 = document.createElement('div');
      div32.setAttribute("class", "form-row");
    var div33 = document.createElement('div');
      div33.setAttribute("class", "form-label-group");
      div33.innerHTML = "Budget ID"; 
    var input11 = document.createElement("input");
      input11.setAttribute("id", "budget_id");
      input11.setAttribute("name", "budget_id");
      input11.setAttribute("class", "form-control");
      input11.setAttribute("type", "text");
      input11.setAttribute("required", "true");
      input11.setAttribute("autofocus", "autofocus");
      input11.setAttribute("readonly", "true");
  
    //DOM submit button
    var submit1 = document.createElement("input");
      submit1.setAttribute("type", "submit");
      submit1.setAttribute("value", "Update Budget");
    
//Append all the DOM elements to the page

//Budget Name
page.appendChild(form1);
  form1.appendChild(div1);
    div1.appendChild(div2);
      div2.appendChild(div3);
        div3.appendChild(input3);
  //Budget Month
  form1.appendChild(div4);
    div4.appendChild(div5);
      div5.appendChild(div6);
        div6.appendChild(input1);
          input1.appendChild(option1);
          input1.appendChild(option2);
          input1.appendChild(option3);
          input1.appendChild(option4);
          input1.appendChild(option5);
          input1.appendChild(option6);
          input1.appendChild(option7);
          input1.appendChild(option8);
          input1.appendChild(option9);
          input1.appendChild(option10);
          input1.appendChild(option11);
          input1.appendChild(option12);
  //Budget Total Available
  form1.appendChild(div7);
    div7.appendChild(div8);
      div8.appendChild(div9);
        div9.appendChild(input2);
  //Budget Target Not To Exceed
  form1.appendChild(div10);
    div10.appendChild(div11);
      div11.appendChild(div12);
        div12.appendChild(input6);
  //Budget Category 1
  form1.appendChild(div13);
    div13.appendChild(div14);
      div14.appendChild(div15);
        div15.appendChild(input4);
          input4.appendChild(bcoption1);
          input4.appendChild(bcoption2);
          input4.appendChild(bcoption3);
  //Budget Target 1
  form1.appendChild(div16);
    div16.appendChild(div17);
      div17.appendChild(div18);
        div18.appendChild(input5);
  //Budget Category 2
  form1.appendChild(div19);
    div19.appendChild(div20);
      div20.appendChild(div21);
        div21.appendChild(input7);
          input7.appendChild(bcoption4);
          input7.appendChild(bcoption5);
          input7.appendChild(bcoption6);
  //Budget Target 2
  form1.appendChild(div22);
    div22.appendChild(div23);
      div23.appendChild(div24);
        div24.appendChild(input8);
  //Budget Category 3
  form1.appendChild(div25);
    div25.appendChild(div26);
      div26.appendChild(div27);
        div27.appendChild(input9);
          input9.appendChild(bcoption7);
          input9.appendChild(bcoption8);
          input9.appendChild(bcoption9);
  //Budget Target 3
  form1.appendChild(div28);
    div28.appendChild(div29);
      div29.appendChild(div30);
        div30.appendChild(input10);
  //Budget ID
  form1.appendChild(div31);
    div31.appendChild(div32);
      div32.appendChild(div33);
        div33.appendChild(input11);

  form1.appendChild(submit1);


//Parse query string to get budget name
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


//Get all the data related to the specified budget
var request = new XMLHttpRequest();
request.open('GET', 'https://cs361group1.appspot.com/budget?name=' + urlParams["name"], true);

request.onload = function () 
{
  
  // Begin accessing JSON data here
  var data = JSON.parse(this.response);
  console.log(data);
  if (request.status >= 200 && request.status < 400) 
  {
      
      //Set the value of the fields in the html document with credentials from user
      
      input1.setAttribute("value", data.budgetMonth);
      if (data.budgetMonth == "January")
      {
          option1.selected = true;
      }
      else if (data.budgetMonth == "February")
      {
          option2.selected = true;
      }
      else if (data.budgetMonth == "March")
      {
          option3.selected = true;
      }
      else if (data.budgetMonth == "April")
      {
          option4.selected = true;
      }
      else if (data.budgetMonth == "May")
      {
          option5.selected = true;
      }
      else if (data.budgetMonth == "June")
      {
          option6.selected = true;
      }
      else if (data.budgetMonth == "July")
      {
          option7.selected = true;
      }
      else if (data.budgetMonth == "August")
      {
          option8.selected = true;
      }
      else if (data.budgetMonth == "September")
      {
          option9.selected = true;
      }
      else if (data.budgetMonth == "October")
      {
          option10.selected = true;
      }
      else if (data.budgetMonth == "November")
      {
          option11.selected = true;
      }
      else if (data.budgetMonth == "December")
      {
          option12.selected = true;
      }
      input2.setAttribute("value", data.totalBudget);
      input3.setAttribute("value", data.name);
      input4.setAttribute("value", data.budgetCategory1);
      if (data.budgetCategory1 == "Grocery")
      {
          bcoption1.selected = true;
      }
      else if (data.budgetCategory1 == "Restaurant")
      {
          bcoption2.selected = true;
      }
      else if (data.budgetCategory1 == "Retail")
      {
          bcoption3.selected = true;
      }
      input5.setAttribute("value", data.targetBudgetCategory1);
      input6.setAttribute("value", data.budgetNotToExceed);
      input7.setAttribute("value", data.budgetCategory2);
      if (data.budgetCategory2 == "Grocery")
      {
          bcoption4.selected = true;
      }
      else if (data.budgetCategory2 == "Restaurant")
      {
          bcoption5.selected = true;
      }
      else if (data.budgetCategory2 == "Retail")
      {
          bcoption6.selected = true;
      }
	   input8.setAttribute("value", data.targetBudgetCategory2);
	   input9.setAttribute("value", data.budgetCategory3);
      if (data.budgetCategory3 == "Grocery")
      {
          bcoption7.selected = true;
      }
      else if (data.budgetCategory3 == "Restaurant")
      {
          bcoption8.selected = true;
      }
      else if (data.budgetCategory3 == "Retail")
      {
          bcoption9.selected = true;
      }
	  input10.setAttribute("value", data.targetBudgetCategory3);
	  input11.setAttribute("value", data.budget_id);

  }

  else
  {
    const errorMessage = document.createElement('marquee');
    errorMessage.textContent = `Gah, it's not working!`;
    app.appendChild(errorMessage);
  }
}

request.send();