

/*********************************************
* Thanks the user for submitting the form
*********************************************/

var bioForm = document.getElementById("bioForm");
var nameDisplay = document.getElementById("nameDisplay");
var messaging = document.getElementById("messaging");

//Validates for a proper email string.
function validateEmail(bioForm)
{
	
	var emailString = /\S+@\S+\.\S+/;


	if (emailString.test(bioForm.email.value))
	{
		console.log(bioForm.email.value);
		return true;
	}
	
	return false;
}


//Gives errors or thanks user upon submission
bioForm.addEventListener("submit", function(event)
{
	event.preventDefault();
	
	//If valid email address and fields submit
	if (validateEmail(bioForm))
	{
		var name = bioForm.userName.value;
		messaging.textContent = "Thank you for your submission " + name + ".";
		
		setTimeout(function() 
		{
     	   bioForm.submit();
    	}, 2000);
    }

    //Invalid Email address string, notify user.
    else
    {
    	messaging.textContent = "Invalid Email Address Format.";
    }
});



