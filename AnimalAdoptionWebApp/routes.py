from flask import *
import os
import secrets
from PIL import Image
from petpair import app, db, bcrypt, login_manager
from petpair.forms import UserRegistrationForm, ShelterRegistrationForm, AddAnimalForm, EditAnimalForm, LoginForm, UserPreferencesForm, UserAccountForm, ShelterAccountForm
from petpair.models import *
import sqlalchemy
from flask_sqlalchemy import SQLAlchemy
import pymysql
from flask_login import login_user, current_user, logout_user, login_required

# ********************************************************************
#	Landing Page Route
# ********************************************************************
@app.route("/")
def index():
    return render_template('landingPage.html')

# ********************************************************************
#	Register Choice Page Route
# ********************************************************************
@app.route("/register-choice")
def registerChoice():
    return render_template('registerChoice.html')

# ********************************************************************
#	User Register Page Route
# ********************************************************************
@app.route("/user-register", methods = ['GET', 'POST'])
def userRegister():
	if current_user.is_authenticated:
		return redirect(url_for('userInterface'))
	form = UserRegistrationForm()
	if form.validate_on_submit():
		try:
			hashed_password = bcrypt.generate_password_hash(form.password.data).decode('utf-8')
			user = User(firstName=form.firstName.data, lastName=form.lastName.data, phone=form.phoneNumber.data, street=form.street.data, city=form.city.data, 
						state=form.state.data, zipCode=form.zipCode.data, aboutMe=form.userDescription.data, password=hashed_password, email=form.email.data)
			account = Account(email=form.email.data, accountType=1)
			db.session.add(user)
			db.session.add(account)
			db.session.commit()

			specieList = request.form.getlist('speciesChecklist')
			dogBreedList = request.form.getlist('dogBreedChecklist')
			catBreedList = request.form.getlist('catBreedChecklist')
			breedList = list()
			for dog in dogBreedList:
				breedList.append(dog)
			for cat in catBreedList:
				breedList.append(cat)
			dispoList = request.form.getlist('dispositionChecklist')

			regUser = User.query.filter_by(email=form.email.data).first()

			# how to add many-to-many relationships
			for specie in specieList:
				specieId = int(specie)
				userSpecie = Species.query.filter_by(specieId=specieId).first()
				userSpecie.user.append(regUser) #variable_name.user_backref.append(commited_user)
				db.session.commit()

			for breed in breedList:
				breedId = int(breed)
				userBreed = BreedTypes.query.filter_by(breedId=breedId).first()
				userBreed.user.append(regUser) 
				db.session.commit()

			for dispo in dispoList:
				dispositionId = int(dispo)
				userDispo = DispositionTypes.query.filter_by(dispositionId=dispositionId).first()
				userDispo.user.append(regUser)
				db.session.commit()
		except Exception as e:
			return Response(status=500, response="Unable to add user. Please try again.")	
		login_user(user)
		flash(f'Account created for {form.email.data}!', 'success')
		return redirect(url_for('userInterface'))
	
	return render_template('userRegister.html', form = form)

# ********************************************************************
#	Shelter Register Page Route
# ********************************************************************
@app.route("/shelter-register", methods = ['GET', 'POST'])
def shelterRegister():
	if current_user.is_authenticated:
		return redirect(url_for('shelterInterface'))
	form = ShelterRegistrationForm()
	if form.validate_on_submit():
		hashed_password = bcrypt.generate_password_hash(form.password.data).decode('utf-8')
		shelter = Shelter(name=form.shelterName.data, phone=form.phoneNumber.data, street=form.street.data, city=form.city.data, 
					state=form.state.data, zipCode=form.zipCode.data, description=form.shelterDescription.data, password=hashed_password, email=form.email.data)
		account = Account(email=form.email.data, accountType=2)
		db.session.add(shelter)
		db.session.add(account)
		db.session.commit()		
		flash(f'Shelter account created for {form.email.data}!', 'success')
		login_user(shelter)
		return redirect(url_for('shelterInterface'))
	return render_template('shelterRegister.html', form = form)

# ********************************************************************
#	User/Shelter Login Page Route
# ********************************************************************
@app.route('/login', methods=['GET', 'POST'])
def login():
	unsuccessful = 'Please check your credentials and try again'
	successful = 'Login successful'
	form = LoginForm()
	if form.validate_on_submit():

		# get account type for email. will throw error if email doesn't exist
		account = Account.query.filter_by(email=form.email.data).first()
		accountType = account.accountType

		# If the login accountType was a value of 1, it is a user
		if accountType == 1:
			user = User.query.filter_by(email=form.email.data).first()
			if user and bcrypt.check_password_hash(user.password, form.password.data):
				login_user(user)
				return redirect(url_for('userInterface'))
			else:
				flash('Login unsuccessful', 'danger')
		
		# If the login accountType was a value of 2, it is a shelter
		elif accountType == 2:
			shelter = Shelter.query.filter_by(email=form.email.data).first()
			if shelter and bcrypt.check_password_hash(shelter.password, form.password.data):
				login_user(shelter)
				return redirect(url_for('shelterInterface'))
			else:
				flash('Login unsuccessful', 'danger')
	
	return render_template('login.html', form=form)

# ********************************************************************
#	Shelter Interface Page Route
# ********************************************************************
@app.route("/shelter-interface", methods = ['GET', 'POST'])
@app.route("/shelter-interface/<int:animalId>", methods = ['GET', 'POST'])
@login_required
def shelterInterface(animalId=0):

	animalsAvailable = Animal.query.filter(Animal.shelterId==current_user.shelterId, Animal.status_id==1).count()
	animalsUnavailable = Animal.query.filter(Animal.shelterId==current_user.shelterId, Animal.status_id==2).count()
	animalsPending = Animal.query.filter(Animal.shelterId==current_user.shelterId, Animal.status_id==3).count()
	animalsAdopted = Animal.query.filter(Animal.shelterId==current_user.shelterId, Animal.status_id==4).count()
	animals = Animal.query.filter_by(shelterId=current_user.shelterId).all()
	breedTypes = BreedTypes.query.all()	

	return render_template('shelterInterface.html', breedTypes=breedTypes, animals=animals, animalsAvailable=animalsAvailable, animalsUnavailable=animalsUnavailable, animalsPending=animalsPending, animalsAdopted=animalsAdopted)

# ********************************************************************
#	Shelter Account Page Route
# ********************************************************************
@app.route("/shelter-account", methods = ['GET', 'POST'])
@login_required
def shelterAccount():
	form = ShelterAccountForm()
	form.shelterName.data = current_user.name
	form.phoneNumber.data = current_user.phone
	form.street.data = current_user.street
	form.city.data = current_user.city
	form.state.data = current_user.state
	form.zipCode.data = current_user.zipCode
	form.shelterDescription.data = current_user.description

	if form.validate_on_submit():
		current_user.name = form.shelterName.data
		current_user.phone = form.phoneNumber.data
		current_user.street = form.street.data
		current_user.city = form.city.data
		current_user.state = form.state.data
		current_user.zipCode = form.zipCode.data
		current_user.description = form.shelterDescription.data

		db.session.commit()

		flash(f'Shelter Account Updated!', 'success')
		return redirect(url_for('shelterInterface'))
	return render_template('shelterAccount.html', form=form)

# ********************************************************************
#	Crop Animal Picture Square Function
# ********************************************************************
def crop_center(originalImage, cropWidth, cropHeight):
	img_width, img_height = originalImage.size
	return originalImage.crop(((img_width - cropWidth) // 2,
						(img_height - cropHeight) // 2,
						(img_width + cropWidth) // 2,
						(img_height + cropHeight) // 2))

# ********************************************************************
#	Save Animal Picture Function
# ********************************************************************
def saveAnimalPicture(formPicture):
    
    # Generate a random hex to append to file name to prevent collisions
    randomHex = secrets.token_hex(8)
    
    # Grabs the originally uploaded files extension, i.e jpg or png
    _, filenameExtension = os.path.splitext(formPicture.filename)
    pictureFileName = randomHex + filenameExtension
    
    # Create the final name/path
    imagePath = os.path.join(app.root_path, 'static/animalPics', pictureFileName)

    # Resize and crop the image before finally saving
    outputSize = (500, 500) # Set final output size
    newImage = Image.open(formPicture) # Open the image
    width, height = newImage.size # Get the width and height of image

    # Determine the shortest side for square cropping and sent to crop function
    if width < height:
    	newImageCropped = crop_center(newImage, width, width)
    elif height < width:
    	newImageCropped = crop_center(newImage, height, height)
    else:
    	newImageCropped = crop_center(newImage, width, height)
    
    # Save the final image
    newImageCropped.thumbnail(outputSize)
    newImageCropped.save(imagePath)

    return pictureFileName


# ********************************************************************
#	Add Animal Page Route
# ********************************************************************
@app.route("/add-animal", methods = ['GET', 'POST'])
@login_required
def addAnimal():
	form = AddAnimalForm()
	if form.validate_on_submit():
		specieId = int(form.animalSpecies.data)
		
		# Get the value from each type of breed field, Default non-answer fields are -1 values
		dogBreedId = int(form.dogBreeds.data)
		catBreedId = int(form.catBreeds.data)
		otherBreedId = int(form.otherBreeds.data)
		
		# Determine if the breed to add is dog, cat, or other by checking for a positive value
		# A positive value only exists with an associated breed, negative values are default/empty fields
		breedId = 0
		animalImageName = ""
		if catBreedId == -1 and otherBreedId == -1:
			breedId = dogBreedId
			animalImageName = "defaultDog.jpg"
		elif dogBreedId == -1 and otherBreedId == -1:
			breedId = catBreedId
			animalImageName = "defaultCat.jpg"
		else:
			breedId = otherBreedId
			animalImageName = "defaultOther.jpg"

		status = int(form.animalStatus.data)
		dispoList = request.form.getlist('dispositionChecklist')
		
		# Call the function to save the image in the correct format
		# pictureFile = saveAnimalPicture(form.animalImage.data)

		animal = Animal(name=form.animalName.data, shelterId=current_user.shelterId, specieId=specieId, 
						breedId=breedId, status_id=status, description=form.animalDescription.data, 
						shelter=current_user, image_file=animalImageName)
		
		db.session.add(animal)
		db.session.commit()

		regAnimal = Animal.query.join(Shelter).filter(Animal.name==form.animalName.data, Shelter.shelterId==current_user.shelterId).first()
		for dispo in dispoList:
			for dispo in dispoList:
				dispositionId = int(dispo)
				userDispo = DispositionTypes.query.filter_by(dispositionId=dispositionId).first()
				userDispo.animal.append(regAnimal)
				db.session.commit()

		flash(f'Animal created for {form.animalName.data}!', 'success')
		return redirect(url_for('shelterInterface'))
	return render_template('addAnimal.html', form=form)

# ********************************************************************
#	Edit Animal Page Route
# ********************************************************************
@app.route("/edit-animal/<int:animalId>", methods = ['GET', 'POST'])
@login_required
def editAnimal(animalId):
	animal = Animal.query.get_or_404(animalId)
	form = EditAnimalForm()
	form.animalName.data = animal.name
	# form.animalBreeds.data = animal.breedId
	form.animalDescription.data = animal.description
	#form.animalStatus.data = animal.status_id
	#form.animalSpecies.data = animal.specieId
	
	animal.disposition = []
	db.session.commit()
	if animal.shelterId != current_user.shelterId:
		abort(403)

	if form.validate_on_submit():
		
		# Get the value from each type of breed field, Default non-answer fields are -1 values
		dogBreedId = int(form.dogBreeds.data)
		catBreedId = int(form.catBreeds.data)
		otherBreedId = int(form.otherBreeds.data)
		
		# Determine if the breed to add is dog, cat, or other by checking for a positive value
		# A positive value only exists with an associated breed, negative values are default/empty fields
		breedId = 0
		animalImageName = ""
		if catBreedId == -1 and otherBreedId == -1:
			breedId = dogBreedId
			animalImageName = "defaultDog.jpg"
		elif dogBreedId == -1 and otherBreedId == -1:
			breedId = catBreedId
			animalImageName = "defaultCat.jpg"
		else:
			breedId = otherBreedId
			animalImageName = "defaultOther.jpg"

		animal.name = form.animalName.data
		animal.specieId = form.animalSpecies.data
		animal.breedId = breedId
		animal.stauts_id = form.animalStatus.data
		animal.description = form.animalDescription.data
		animal.image_file = animalImageName
		db.session.commit()


		dispoList = request.form.getlist('dispositionChecklist')
		for dispo in dispoList:
			dispositionId = int(dispo)
			userDispo = DispositionTypes.query.filter_by(dispositionId=dispositionId).first()
			userDispo.animal.append(animal)
			db.session.commit()
		flash(f'Animal Updated!', 'success')
		return redirect(url_for('shelterInterface'))
	return render_template('editAnimal.html', form=form)

# ********************************************************************
#	User Interface Page Route
# ********************************************************************
@app.route("/user-interface", methods = ['GET', 'POST'])
@app.route("/user-interface/<int:animalId>", methods = ['GET', 'POST'])
@login_required
def userInterface(animalId=0):

	breedTypes = BreedTypes.query.all()
	favorites = Animal.query.filter(Animal.userFavorite.any(userId=current_user.userId)).all()
	dispoListQuery = db.session.query(DispositionTypes.dispositionId).filter(DispositionTypes.user.any(userId=current_user.userId))
	breedPrefQuery = db.session.query(BreedTypes.breedId).filter(BreedTypes.user.any(userId=current_user.userId))
	dislikes = Animal.query.filter(Animal.userDislikes.any(userId=current_user.userId)).all()

	matchSet = Animal.query.filter(Animal.dispoOf.any(DispositionTypes.dispositionId.in_(dispoListQuery))).filter(Animal.breedId.in_(breedPrefQuery)).all()

	matches = []

	for m in matchSet:
		if m in favorites or m in dislikes:
			continue
		else:
			matches.append(m)
	
	if len(matches) == 0 and len(favorites) == 0:
		return redirect(url_for('userInterfaceNoMatches'))

	if animalId == 0:
		if len(matches) != 0:	
			selectedAnimal = matches[0]
		else:
			selectedAnimal = favorites[0]
	else:
		selectedAnimal = Animal.query.get(animalId)

	selectedAnimalDispoList = DispositionTypes.query.filter(DispositionTypes.animal.any(animalId=selectedAnimal.animalId)).all()
	selectedAnimalShelter = Shelter.query.get(selectedAnimal.shelterId)
	selectedAnimalStatus = Status.query.get(selectedAnimal.status_id)
	return render_template('userInterface.html', favorites=favorites, selectedAnimalStatus=selectedAnimalStatus, selectedAnimalShelter=selectedAnimalShelter, breedTypes=breedTypes, matches=matches, selectedAnimal=selectedAnimal, selectedAnimalDispoList=selectedAnimalDispoList)


# ********************************************************************
#	User Preferences Page Route
# ********************************************************************
@app.route("/user-preferences", methods = ['GET', 'POST'])
def userPreferences():
	form = UserPreferencesForm()
	if form.validate_on_submit():
		current_user.prefersDisposition = []
		current_user.prefersSpecies = []
		current_user.prefersBreed = []
		db.session.commit()

		dispoList = request.form.getlist('dispositionChecklist')
		for dispo in dispoList:
			dispositionId = int(dispo)
			userDispo = DispositionTypes.query.filter_by(dispositionId=dispositionId).first()
			userDispo.user.append(current_user)

		speciesList = request.form.getlist('speciesChecklist')
		for specie in speciesList:
			specieId = int(specie)
			userSpecie = Species.query.filter_by(specieId=specieId).first()
			userSpecie.user.append(current_user)

		dogBreedList = request.form.getlist('dogBreedChecklist')
		catBreedList = request.form.getlist('catBreedChecklist')
		breedList = list()
		for dog in dogBreedList:
			breedList.append(dog)
		for cat in catBreedList:
			breedList.append(cat)

		for breed in breedList:
			breedId = int(breed)
			userBreed = BreedTypes.query.filter_by(breedId=breedId).first()
			userBreed.user.append(current_user)
		db.session.commit()

		return redirect(url_for('userInterface'))
	return render_template('userPreferences.html', form=form)

# ********************************************************************
#	User Account Page Route
# ********************************************************************
@app.route("/user-account", methods = ['GET', 'POST'])
def userAccount():
	form = UserAccountForm()
	
	form.firstName.data = current_user.firstName
	form.lastName.data = current_user.lastName
	form.phoneNumber.data = current_user.phone
	form.street.data = current_user.street
	form.city.data = current_user.city
	form.state.data = current_user.state
	form.zipCode.data = current_user.zipCode
	form.userDescription.data = current_user.aboutMe
	
	if form.validate_on_submit():
		current_user.firstName = form.firstName.data
		current_user.lastName = form.lastName.data
		current_user.phone = form.phoneNumber.data
		current_user.street = form.street.data
		current_user.city = form.city.data
		current_user.state = form.state.data
		current_user.zipCode = form.zipCode.data
		current_user.aboutMe = form.userDescription.data

		db.session.commit()

		flash(f'User Updated!', 'success')
		return redirect(url_for('userInterface'))

	return render_template('userAccount.html', form=form)
	
# ********************************************************************
#  User Log Out Route
# ********************************************************************
@app.route("/logout")
def logout():
	logout_user()
	return redirect(url_for('index'))

# ********************************************************************
#  Add to favorites
# ********************************************************************
@app.route("/add-favorite/<int:animalId>", methods = ['GET', 'POST'])
def addFavorite(animalId):
	animal = Animal.query.get_or_404(animalId)
	user = User.query.get(current_user.userId)
	animal.userFavorite.append(user)
	db.session.commit()
	return redirect(url_for('userInterface'))

# ********************************************************************
#  Add to dislikes
# ********************************************************************
@app.route("/add-dislike/<int:animalId>", methods = ['GET', 'POST'])
def addDislike(animalId):
	animal = Animal.query.get_or_404(animalId)
	user = User.query.get(current_user.userId)
	favorites = Animal.query.filter(Animal.userFavorite.any(userId=current_user.userId)).all()
	for fav in favorites:
		if fav.animalId == animal.animalId:
			animal.userFavorite.remove(user)
	animal.userDislikes.append(user)
	db.session.commit()
	return redirect(url_for('userInterface'))

# ********************************************************************
#  Delete Animal
# ********************************************************************
@app.route("/delete-animal/<int:animalId>", methods = ['GET', 'POST'])
def deleteAnimal(animalId):
	animal = Animal.query.get_or_404(animalId)
	db.session.delete(animal)
	db.session.commit()
	return redirect(url_for('shelterInterface'))

# ********************************************************************
#  User Interface No Matches Route
# ********************************************************************
@app.route("/user-interface-no-matches", methods = ['GET', 'POST'])
@login_required
def userInterfaceNoMatches():
	return render_template('userInterfaceNoMatches.html')