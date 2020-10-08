

/******************************************
* Change opacity on download hover
******************************************/

const element1 = document.querySelector("#dHover1");
const element2 = document.querySelector("#dHover2");
const element3 = document.querySelector("#dHover3");

element1.addEventListener("mouseover", event =>
{
	dHover1.style.opacity = 0.5;
});

element1.addEventListener("mouseout", event => 
{
	dHover1.style.opacity = 1;
});

element2.addEventListener("mouseover", event =>
{
	dHover2.style.opacity = 0.5;
});

element2.addEventListener("mouseout", event => 
{
	dHover2.style.opacity = 1;
});

element3.addEventListener("mouseover", event =>
{
	dHover3.style.opacity = 0.5;
});

element3.addEventListener("mouseout", event => 
{
	dHover3.style.opacity = 1;
});



/******************************************
* Shows the current date in the footer.
******************************************/
var displayTheDate = document.getElementById("displayTheDate");

function showCurrentDate()
{
    var theDate = new Date();
    var currentDate = theDate.getDate();
    var currentMonth = theDate.getMonth() + 1;
    var currentYear = theDate.getFullYear();

	return currentMonth + "-" + currentDate + "-" + currentYear;
}

displayTheDate.textContent = showCurrentDate();