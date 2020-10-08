from flask_wtf import FlaskForm
from flask_wtf.file import FileField, FileAllowed
from wtforms import StringField, PasswordField, SubmitField, IntegerField, SelectField, BooleanField, RadioField, DateTimeField
from wtforms.validators import DataRequired, Length, Email, EqualTo, email_validator, ValidationError
from petpair.models import *


# ********************************************************************
#	UserRegistrationForm()
# ********************************************************************
# User Registration Form class, it inherits from 'FlaskForm'
# This form is used for users looking to find/adopt a pet
class UserRegistrationForm(FlaskForm):
	# User personal information fields
	email = StringField('Email', validators = [DataRequired(), Email()])
	password = PasswordField('Password', validators = [DataRequired()])
	confirmPassword = PasswordField('Confirm Password', validators = [DataRequired(), EqualTo('password')])
	firstName = StringField('First Name', validators = [DataRequired(), Length(min = 1, max = 30)])
	lastName = StringField('Last Name', validators = [DataRequired(), Length(min = 1, max = 30)])
	phoneNumber = IntegerField('Phone Number', validators = [DataRequired()])
	street = StringField('Street Address', validators = [DataRequired(), Length(min = 1, max = 30)])
	city = StringField('City', validators = [DataRequired(), Length(min = 1, max = 30)])
	state = SelectField('State', choices = [('AL', 'Alabama'), ('AK', 'Alaska'), ('AZ', 'Arizona'), ('AR', 'Arkansas'), ('CA', 'California'), ('CO', 'Colorado'), ('CT', 'Connecticut'), ('DE', 'Delaware'),
											('FL', 'Florida'), ('GA', 'Georgia'), ('HI', 'Hawaii'), ('ID', 'Idaho'), ('IL', 'Illinois'), ('IN', 'Indiana'), ('IA', 'Iowa'), ('KS', 'Kansas'),
											('KY', 'Kentucky'), ('LA', 'Louisiana'), ('ME', 'Maine'), ('MD', 'Maryland'), ('MA', 'Massachusetts'), ('MI', 'Michigan'), ('MN', 'Minnesota'),
											('MS', 'Mississippi'), ('MO', 'Missouri'), ('MT', 'Montana'), ('NE', 'Nebraska'), ('NV', 'Nevada'), ('NH', 'New Hampshire'), ('NJ', 'New Jersey'),
											('NM', 'New Mexico'), ('NY', 'New York'), ('NC', 'North Carolina'), ('ND', 'North Dakota'), ('OH', 'Ohio'), ('OK', 'Oklahoma'), ('OR', 'Oregon'),
											('PA', 'Pennsylvania'), ('RI', 'Rhode Island'), ('SC', 'South Carolina'), ('SD', 'South Dakota'), ('TN', 'Tennessee'), ('TX', 'Texas'),
											('UT', 'Utah'), ('VT', 'Vermont'), ('VA', 'Virginia'), ('WA', 'Washington'), ('WV', 'West Virginia'), ('WI', 'Wisconsin'), ('WY', 'Wyoming')])
	zipCode = IntegerField('Zip Code', validators = [DataRequired()])
	userDescription = StringField('Describe Yourself', validators = [DataRequired(), Length(min = 1, max = 255)])

	# Animal Type Fields
	animalTypeDog = BooleanField('Dog')
	animalTypeCat = BooleanField('Cat')
	animalTypeOther = BooleanField('Other')

	# Dog Species Fields
	dogSpecieBeagle = BooleanField('Beagle')
	dogSpecieBulldog = BooleanField('Bulldog')
	dogSpecieChihuahua = BooleanField('Chihuahua')
	dogSpecieDachshund = BooleanField('Dachshund')
	dogSpecieGreatDane = BooleanField('Great Dane')
	dogSpecieGreyhound = BooleanField('Greyhound')
	dogSpecieJackRussellTerrier = BooleanField('Jack Russell Terrier')
	dogSpecieLabradorRetriever = BooleanField('Labrador Retriever')
	dogSpeciePoodle = BooleanField('Poodle')
	dogSpecieRottweiler = BooleanField('Rottweiler')

	# Cat Species Fields
	catSpecieBengal = BooleanField('Bengal')
	catSpecieBurmese = BooleanField('Burmese')
	catSpecieManx = BooleanField('Manx')
	catSpecieMunchkin = BooleanField('Munchkin')
	catSpeciePersian = BooleanField('Persian')
	catSpecieRagamuffin = BooleanField('Ragamuffin')
	catSpecieSiamese = BooleanField('Siamese')
	catSpecieSiberian = BooleanField('Siberian')
	catSpecieTabby = BooleanField('Tabby')
	catSpecieWirehair = BooleanField('Wirehair')

	# Disposition Fields
	dispositionGWOA = BooleanField('Good With Other Animals')
	dispositionGWC = BooleanField('Good With Children')
	dispositionAMBLAAT = BooleanField('Animal Must Be Leashed At All Times')
	dispositionBarks = BooleanField('Barks')
	dispositionDoesntBark = BooleanField('Doesnt Bark')
	dispositionDeclawed = BooleanField('Declawed')
	dispositionHypoallergenic = BooleanField('Hypoallergenic')
	dispositionHyperactive = BooleanField('Hyperactive')
	dispositionRelaxed = BooleanField('Relaxed')
	dispositionTrained = BooleanField('Trained')
	dispositionNeedsTraining = BooleanField('Needs Training')

	# Final Submit Field
	submit = SubmitField('Register')

	def validate_email(self, email):
		user = Account.query.filter_by(email=email.data).first()
		if user:
			raise ValidationError('User account with this email already exists')



# ********************************************************************
#	ShelterRegistrationForm()
# ********************************************************************
# Shelter Registration Form class, it inherits from 'FlaskForm'
# This form is used for shelters looking to post pets for adoption
class ShelterRegistrationForm(FlaskForm):
	# Shelter information fields
	email = StringField('Email', validators = [DataRequired(), Email()])
	password = PasswordField('Password', validators = [DataRequired()])
	confirmPassword = PasswordField('Confirm Password', validators = [DataRequired(), EqualTo('password')])
	shelterName = StringField('Shelter Name', validators = [DataRequired(), Length(min = 1, max = 50)])
	phoneNumber = IntegerField('Phone Number', validators = [DataRequired()])
	street = StringField('Street Address', validators = [DataRequired(), Length(min = 1, max = 30)])
	city = StringField('City', validators = [DataRequired(), Length(min = 1, max = 30)])
	state = SelectField('State', choices = [('AL', 'Alabama'), ('AK', 'Alaska'), ('AZ', 'Arizona'), ('AR', 'Arkansas'), ('CA', 'California'), ('CO', 'Colorado'), ('CT', 'Connecticut'), ('DE', 'Delaware'),
											('FL', 'Florida'), ('GA', 'Georgia'), ('HI', 'Hawaii'), ('ID', 'Idaho'), ('IL', 'Illinois'), ('IN', 'Indiana'), ('IA', 'Iowa'), ('KS', 'Kansas'),
											('KY', 'Kentucky'), ('LA', 'Louisiana'), ('ME', 'Maine'), ('MD', 'Maryland'), ('MA', 'Massachusetts'), ('MI', 'Michigan'), ('MN', 'Minnesota'),
											('MS', 'Mississippi'), ('MO', 'Missouri'), ('MT', 'Montana'), ('NE', 'Nebraska'), ('NV', 'Nevada'), ('NH', 'New Hampshire'), ('NJ', 'New Jersey'),
											('NM', 'New Mexico'), ('NY', 'New York'), ('NC', 'North Carolina'), ('ND', 'North Dakota'), ('OH', 'Ohio'), ('OK', 'Oklahoma'), ('OR', 'Oregon'),
											('PA', 'Pennsylvania'), ('RI', 'Rhode Island'), ('SC', 'South Carolina'), ('SD', 'South Dakota'), ('TN', 'Tennessee'), ('TX', 'Texas'),
											('UT', 'Utah'), ('VT', 'Vermont'), ('VA', 'Virginia'), ('WA', 'Washington'), ('WV', 'West Virginia'), ('WI', 'Wisconsin'), ('WY', 'Wyoming')])
	zipCode = IntegerField('Zip Code', validators = [DataRequired()])
	shelterDescription = StringField('Describe Your Shelter', validators = [DataRequired(), Length(min = 1, max = 255)])

	# Final Submit Field
	submit = SubmitField('Register')

	def validate_email(self, email):
		shelter = Account.query.filter_by(email=email.data).first()
		if shelter:
			raise ValidationError('Shelter account with this email already exists')



# ********************************************************************
#	AddAnimalForm()
# ********************************************************************
# Add Animal Form class, it inherits from 'FlaskForm'
# This form is used for shelters trying to add pets for adoption
class AddAnimalForm(FlaskForm):

	# Add Animal information fields
	animalName = StringField('Animal Name', validators = [DataRequired(), Length(min = 1, max = 20)])
	animalSpecies = SelectField('Species', choices = [("", "-- Select An Option --"), ('1', 'Dog'), ('2', 'Cat'), ('3', 'Other')], default=-1, validators = [DataRequired()])
	
	#dateOfBirth = DateTimeField('Birth Date', format='%m/%d/%Y', default='01/01/9999')
	
	dogBreeds = SelectField('Dog Breed', choices = [('-1', "-- Select An Option --"), ('1', 'Beagle'), ('2', 'Bulldog'), ('3', 'Chihuahua'), 
													('4', 'Dachshund'), ('5','Great Dane'), ('6', 'Greyhound'), ('7', 'Jack Russell Terrier'), 
													('8', 'Labrador Retriever'), ('9', 'Poodle'), ('10', 'Rottweiler')], validators = [DataRequired()])
	
	catBreeds = SelectField('Cat Breed', choices = [('-1', "-- Select An Option --"), ('11', 'Bengal'),('12', 'Burmese'), ('13', 'Manx'), 
													('14', 'Munchkin'), ('15', 'Persian'), ('16', 'Ragamuffin'), ('17', 'Siamese'), 
													('18', 'Siberian'), ('19', 'Tabby'), ('20', 'Wirehair')], validators = [DataRequired()])
	
	otherBreeds = SelectField('Type Of Animal', choices = [('-1', "-- Select An Option --"), ('21', 'Bird'), ('22', 'Ferret'), ('23', 'Guinea Pig'), 
															('24', 'Hamster'), ('25', 'Rabbit')], validators = [DataRequired()])
	
	animalStatus = SelectField('Animal Status', choices = [("", "-- Select An Option --"), ('1', 'Available'), ('2', 'Unavailable'), ('3', 'Pending'), 
															('4', 'Adopted')], validators = [DataRequired()])
	
	animalDescription = StringField('Animal Description', validators = [DataRequired(), Length(min = 1, max = 255)])

	dispositionGWOA = BooleanField('Good With Other Animals')
	dispositionGWC = BooleanField('Good With Children')
	dispositionAMBLAAT = BooleanField('Animal Must Be Leashed At All Times')
	dispositionBarks = BooleanField('Barks')
	dispositionDoesntBark = BooleanField('Doesnt Bark')
	dispositionDeclawed = BooleanField('Declawed')
	dispositionHypoallergenic = BooleanField('Hypoallergenic')
	dispositionHyperactive = BooleanField('Hyperactive')
	dispositionRelaxed = BooleanField('Relaxed')
	dispositionTrained = BooleanField('Trained')
	dispositionNeedsTraining = BooleanField('Needs Training')

	# animalImage = FileField('', validators=[DataRequired(), FileAllowed(['jpg', 'png'])])
	
	# Final Submit Field
	submit = SubmitField('Add Animal')



# ********************************************************************
#	EditAnimalForm()
# ********************************************************************
# Edit Animal Form class, it inherits from 'FlaskForm'
# This form is used for shelters trying to edit pets for adoption
class EditAnimalForm(FlaskForm):

	# Add Animal information fields
	animalName = StringField('Animal Name', validators = [DataRequired(), Length(min = 1, max = 20)])
	animalSpecies = SelectField('Species', choices = [("", "-- Select An Option --"), ('1', 'Dog'), ('2', 'Cat'), ('3', 'Other')], default=-1, validators = [DataRequired()])
	
	#dateOfBirth = DateTimeField('Birth Date', format='%m/%d/%Y', default='01/01/9999')
	
	dogBreeds = SelectField('Dog Breed', choices = [('-1', "-- Select An Option --"), ('1', 'Beagle'), ('2', 'Bulldog'), ('3', 'Chihuahua'), 
													('4', 'Dachshund'), ('5','Great Dane'), ('6', 'Greyhound'), ('7', 'Jack Russell Terrier'), 
													('8', 'Labrador Retriever'), ('9', 'Poodle'), ('10', 'Rottweiler')], validators = [DataRequired()])
	
	catBreeds = SelectField('Cat Breed', choices = [('-1', "-- Select An Option --"), ('11', 'Bengal'),('12', 'Burmese'), ('13', 'Manx'), 
													('14', 'Munchkin'), ('15', 'Persian'), ('16', 'Ragamuffin'), ('17', 'Siamese'), 
													('18', 'Siberian'), ('19', 'Tabby'), ('20', 'Wirehair')], validators = [DataRequired()])
	
	otherBreeds = SelectField('Type Of Animal', choices = [('-1', "-- Select An Option --"), ('21', 'Bird'), ('22', 'Ferret'), ('23', 'Guinea Pig'), 
															('24', 'Hamster'), ('25', 'Rabbit')], validators = [DataRequired()])
	
	animalStatus = SelectField('Animal Status', choices = [("", "-- Select An Option --"), ('1', 'Available'), ('2', 'Unavailable'), ('3', 'Pending'), 
															('4', 'Adopted')], validators = [DataRequired()])
	
	animalDescription = StringField('Animal Description', validators = [DataRequired(), Length(min = 1, max = 255)])

	dispositionGWOA = BooleanField('Good With Other Animals')
	dispositionGWC = BooleanField('Good With Children')
	dispositionAMBLAAT = BooleanField('Animal Must Be Leashed At All Times')
	dispositionBarks = BooleanField('Barks')
	dispositionDoesntBark = BooleanField('Doesnt Bark')
	dispositionDeclawed = BooleanField('Declawed')
	dispositionHypoallergenic = BooleanField('Hypoallergenic')
	dispositionHyperactive = BooleanField('Hyperactive')
	dispositionRelaxed = BooleanField('Relaxed')
	dispositionTrained = BooleanField('Trained')
	dispositionNeedsTraining = BooleanField('Needs Training')

	# animalImage = FileField('', validators=[DataRequired(), FileAllowed(['jpg', 'png'])])
	
	# Final Submit Field
	submit = SubmitField('Update Animal')



# ********************************************************************
#    LoginForm()
# ********************************************************************
# Login class,  inherits from 'FlaskForm'
# Used to login to the app
class LoginForm(FlaskForm):
	email = StringField('Email',
							validators=[DataRequired(), Email()])
	password = PasswordField('Password', 
									validators=[DataRequired()])
	remember = BooleanField('Remember Me')
	submit = SubmitField('Log In')



# ********************************************************************
#	UserPreferencesForm()
# ********************************************************************
# User Preferences Form class, it inherits from 'FlaskForm'
# This form is used for users to update their preferences any point after they have registered
class UserPreferencesForm(FlaskForm):

	# Animal Type Fields
	animalTypeDog = BooleanField('Dog')
	animalTypeCat = BooleanField('Cat')
	animalTypeOther = BooleanField('Other')

	# Dog Species Fields
	dogSpecieBeagle = BooleanField('Beagle')
	dogSpecieBulldog = BooleanField('Bulldog')
	dogSpecieChihuahua = BooleanField('Chihuahua')
	dogSpecieDachshund = BooleanField('Dachshund')
	dogSpecieGreatDane = BooleanField('Great Dane')
	dogSpecieGreyhound = BooleanField('Greyhound')
	dogSpecieJackRussellTerrier = BooleanField('Jack Russell Terrier')
	dogSpecieLabradorRetriever = BooleanField('Labrador Retriever')
	dogSpeciePoodle = BooleanField('Poodle')
	dogSpecieRottweiler = BooleanField('Rottweiler')

	# Cat Species Fields
	catSpecieBengal = BooleanField('Bengal')
	catSpecieBurmese = BooleanField('Burmese')
	catSpecieManx = BooleanField('Manx')
	catSpecieMunchkin = BooleanField('Munchkin')
	catSpeciePersian = BooleanField('Persian')
	catSpecieRagamuffin = BooleanField('Ragamuffin')
	catSpecieSiamese = BooleanField('Siamese')
	catSpecieSiberian = BooleanField('Siberian')
	catSpecieTabby = BooleanField('Tabby')
	catSpecieWirehair = BooleanField('Wirehair')

	# Disposition Fields
	dispositionGWOA = BooleanField('Good With Other Animals')
	dispositionGWC = BooleanField('Good With Children')
	dispositionAMBLAAT = BooleanField('Animal Must Be Leashed At All Times')
	dispositionBarks = BooleanField('Barks')
	dispositionDoesntBark = BooleanField('Doesnt Bark')
	dispositionDeclawed = BooleanField('Declawed')
	dispositionHypoallergenic = BooleanField('Hypoallergenic')
	dispositionHyperactive = BooleanField('Hyperactive')
	dispositionRelaxed = BooleanField('Relaxed')
	dispositionTrained = BooleanField('Trained')
	dispositionNeedsTraining = BooleanField('Needs Training')

	# Final Submit Field
	submit = SubmitField('Update')



# ********************************************************************
#	UserAccountForm()
# ********************************************************************
# User Account Form class, it inherits from 'FlaskForm'
# This form is used for users to update their personal information
class UserAccountForm(FlaskForm):

	# User personal information fields
	firstName = StringField('First Name', validators = [DataRequired(), Length(min = 1, max = 30)])
	lastName = StringField('Last Name', validators = [DataRequired(), Length(min = 1, max = 30)])
	phoneNumber = IntegerField('Phone Number', validators = [DataRequired()])
	street = StringField('Street Address', validators = [DataRequired(), Length(min = 1, max = 30)])
	city = StringField('City', validators = [DataRequired(), Length(min = 1, max = 30)])
	state = SelectField('State', choices = [('AL', 'Alabama'), ('AK', 'Alaska'), ('AZ', 'Arizona'), ('AR', 'Arkansas'), ('CA', 'California'), ('CO', 'Colorado'), ('CT', 'Connecticut'), ('DE', 'Delaware'),
											('FL', 'Florida'), ('GA', 'Georgia'), ('HI', 'Hawaii'), ('ID', 'Idaho'), ('IL', 'Illinois'), ('IN', 'Indiana'), ('IA', 'Iowa'), ('KS', 'Kansas'),
											('KY', 'Kentucky'), ('LA', 'Louisiana'), ('ME', 'Maine'), ('MD', 'Maryland'), ('MA', 'Massachusetts'), ('MI', 'Michigan'), ('MN', 'Minnesota'),
											('MS', 'Mississippi'), ('MO', 'Missouri'), ('MT', 'Montana'), ('NE', 'Nebraska'), ('NV', 'Nevada'), ('NH', 'New Hampshire'), ('NJ', 'New Jersey'),
											('NM', 'New Mexico'), ('NY', 'New York'), ('NC', 'North Carolina'), ('ND', 'North Dakota'), ('OH', 'Ohio'), ('OK', 'Oklahoma'), ('OR', 'Oregon'),
											('PA', 'Pennsylvania'), ('RI', 'Rhode Island'), ('SC', 'South Carolina'), ('SD', 'South Dakota'), ('TN', 'Tennessee'), ('TX', 'Texas'),
											('UT', 'Utah'), ('VT', 'Vermont'), ('VA', 'Virginia'), ('WA', 'Washington'), ('WV', 'West Virginia'), ('WI', 'Wisconsin'), ('WY', 'Wyoming')])
	zipCode = IntegerField('Zip Code', validators = [DataRequired()])
	userDescription = StringField('Describe Yourself', validators = [DataRequired(), Length(min = 1, max = 255)])

	# Final Submit Field
	submit = SubmitField('Update')
	


# ********************************************************************
#	ShelterAccountForm()
# ********************************************************************
# Shelter Account Form class, it inherits from 'FlaskForm'
# This form is used for shelters to edit and change their account info
class ShelterAccountForm(FlaskForm):
	# Shelter information fields
	shelterName = StringField('Shelter Name', validators = [DataRequired(), Length(min = 1, max = 50)])
	phoneNumber = IntegerField('Phone Number', validators = [DataRequired()])
	street = StringField('Street Address', validators = [DataRequired(), Length(min = 1, max = 30)])
	city = StringField('City', validators = [DataRequired(), Length(min = 1, max = 30)])
	state = SelectField('State', choices = [('AL', 'Alabama'), ('AK', 'Alaska'), ('AZ', 'Arizona'), ('AR', 'Arkansas'), ('CA', 'California'), ('CO', 'Colorado'), ('CT', 'Connecticut'), ('DE', 'Delaware'),
											('FL', 'Florida'), ('GA', 'Georgia'), ('HI', 'Hawaii'), ('ID', 'Idaho'), ('IL', 'Illinois'), ('IN', 'Indiana'), ('IA', 'Iowa'), ('KS', 'Kansas'),
											('KY', 'Kentucky'), ('LA', 'Louisiana'), ('ME', 'Maine'), ('MD', 'Maryland'), ('MA', 'Massachusetts'), ('MI', 'Michigan'), ('MN', 'Minnesota'),
											('MS', 'Mississippi'), ('MO', 'Missouri'), ('MT', 'Montana'), ('NE', 'Nebraska'), ('NV', 'Nevada'), ('NH', 'New Hampshire'), ('NJ', 'New Jersey'),
											('NM', 'New Mexico'), ('NY', 'New York'), ('NC', 'North Carolina'), ('ND', 'North Dakota'), ('OH', 'Ohio'), ('OK', 'Oklahoma'), ('OR', 'Oregon'),
											('PA', 'Pennsylvania'), ('RI', 'Rhode Island'), ('SC', 'South Carolina'), ('SD', 'South Dakota'), ('TN', 'Tennessee'), ('TX', 'Texas'),
											('UT', 'Utah'), ('VT', 'Vermont'), ('VA', 'Virginia'), ('WA', 'Washington'), ('WV', 'West Virginia'), ('WI', 'Wisconsin'), ('WY', 'Wyoming')])
	zipCode = IntegerField('Zip Code', validators = [DataRequired()])
	shelterDescription = StringField('Describe Your Shelter', validators = [DataRequired(), Length(min = 1, max = 255)])

	# Final Submit Field
	submit = SubmitField('Update')
