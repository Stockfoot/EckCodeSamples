"""*********************************************************************************************************************
*   Program:        test_calculator.py
*   Date:           2/24/2020
*   Authors:        Russell Eck, Morgan Eck, Michael Payne
*   Description:    This file contains the test suite for the final calculator program. It references the calculator.py
*                   file which only holds the function declarations and no actual code.
*********************************************************************************************************************"""

import calculator

"""*********************************************************************************************************************
***     UNIT TEST FOR MULTIPLICATION
*********************************************************************************************************************"""
def test_multiplication():
    # test multiplication with expected integer values
    assert calculator.Multiplication(2, 3) == 6
    assert calculator.Multiplication(3, 2) == 6
    assert calculator.Multiplication(2, 4) == 8
    assert calculator.Multiplication(50, 50) == 2500
    assert calculator.Multiplication(100, 100) == 10000

    # test a 0 multiplier with various multiplicands
    assert calculator.Multiplication(0, 0) == 0
    assert calculator.Multiplication(0, 1) == 0
    assert calculator.Multiplication(1, 0) == 0
    assert calculator.Multiplication(0, 100) == 0

    # test a 1 multiplier with various multiplicands
    assert calculator.Multiplication(1, 1) == 1
    assert calculator.Multiplication(1, 2) == 2
    assert calculator.Multiplication(2, 1) == 2
    assert calculator.Multiplication(1, 100) == 100

    # test a negative multiplier with a positive multiplicand to ensure negative outcome
    assert calculator.Multiplication(-1, 1) == -1
    assert calculator.Multiplication(1, -1) == -1
    assert calculator.Multiplication(-2, 1) == -2
    assert calculator.Multiplication(-1, 100) == -100

    # test a negative multiplier with a negative multiplicand to ensure positive outcome
    assert calculator.Multiplication(-1, -1) == 1
    assert calculator.Multiplication(-2, -1) == 2
    assert calculator.Multiplication(-50, -50) == 2500
    assert calculator.Multiplication(-1, -100) == 100

    # test a fraction/floating-point multiplier with various multiplicands
    assert calculator.Multiplication(1.5, 1) == 1.5
    assert calculator.Multiplication(1, 1.5) == 1.5
    assert calculator.Multiplication(2.5, 2.5) == 6.25
    assert calculator.Multiplication(100.007, 90.1) == 9010.6307

    # test edge cases, very large/very small values, and positives and negatives
    assert calculator.Multiplication(2147483648, 1) == 2147483648
    assert calculator.Multiplication(1, -2147483648) == -2147483648
    assert calculator.Multiplication(0.000002, 0.000002) == 0.000000000004
    assert calculator.Multiplication(-0.00000001, 2) == -0.00000002


"""*********************************************************************************************************************
***     UNIT TEST FOR DIVISION
*********************************************************************************************************************"""
def test_division():
    # Test division with normal expected integer values
    assert calculator.Division(2, 2) == 1
    assert calculator.Division(10000, 10) == 1000
    assert calculator.Division(49, 7) == 7
    assert calculator.Division(45, 5) == 9
    assert calculator.Division(120, 12) == 10

    # Test division with a zero numerator and any denominator, should always return zero
    assert calculator.Division(0, 1000000) == 0
    assert calculator.Division(0, 235325) == 0
    assert calculator.Division(0, 4) == 0
    assert calculator.Division(0, -12451212) == 0
    assert calculator.Division(0, -10) == 0

    # Test division with negative and positive combinations
    # One negative and one positive should return a negative value
    # Two negatives should return a positive value
    assert calculator.Division(-4, -2) == 2
    assert calculator.Division(-1000, 10) == -100
    assert calculator.Division(16, -4) == -4
    assert calculator.Division(-123456, -123456) == 1
    assert calculator.Division(-500, 50) == -10

    # Test division with different combinations of fractions or floating point values
    assert calculator.Division(5.75, 2) == 2.875
    assert calculator.Division(-200.5, 100.25) == -2
    assert calculator.Division(-10.5, -10500) == 0.001
    assert calculator.Division(2.5, 5) == 0.5
    assert calculator.Division(400, 3.2) == 125

    # Test division with a zero denominator, should return an error
    assert calculator.Division(-4, 0) == "Cannot divide by zero"
    assert calculator.Division(-10002323, 0) == "Cannot divide by zero"
    assert calculator.Division(0.00234, 0) == "Cannot divide by zero"
    assert calculator.Division(123456456, 0) == "Cannot divide by zero"
    assert calculator.Division(-500.2356623, 0) == "Cannot divide by zero"

    # Test division with a one numerator, should return the denominator
    assert calculator.Division(1, 1) == 1
    assert calculator.Division(0, 1) == 0
    assert calculator.Division(-4, 1) == -4
    assert calculator.Division(-10002323, 1) == -10002323
    assert calculator.Division(0.00234, 1) == 0.00234
    assert calculator.Division(123456456, 1) == 123456456

    # Test division with edge cases, long integer values, numbers with large number of decimal values
    assert calculator.Division(-2000000000, 2000000000) == -1
    assert calculator.Division(1, 2000000000) == 0.0000000005
    assert calculator.Division(2, 0.000000005) == 400000000
    assert calculator.Division(500.5000005, 2) == 250.25000025
    assert calculator.Division(-80000.00005, -2) == 40000.000025


"""*********************************************************************************************************************
***     UNIT TEST FOR SQUARE ROOT
*********************************************************************************************************************"""
def test_square_root():
    # test SquareRoot with positive integer values
    assert calculator.SquareRoot(4) == 2
    assert calculator.SquareRoot(100) == 10
    assert calculator.SquareRoot(323) == 17.97220075561143
    assert calculator.SquareRoot(16) == 4
    assert calculator.SquareRoot(99) == 9.9498743710662

    # test SquareRoot with positive floating point values
    assert calculator.SquareRoot(3.75) == 1.9364916731037085
    assert calculator.SquareRoot(12.7846) == 3.575555900835561
    assert calculator.SquareRoot(1.1) == 1.0488088481701516
    assert calculator.SquareRoot(500.24) == 22.36604569431083
    assert calculator.SquareRoot(7.58) == 2.753179979587241

    # test SquareRoot with numbers that should generate integer values
    assert calculator.SquareRoot(25) == 5
    assert calculator.SquareRoot(121) == 11
    assert calculator.SquareRoot(64) == 8
    assert calculator.SquareRoot(81) == 9
    assert calculator.SquareRoot(9) == 3

    # test SquareRoot with numbers that should generate floating point values
    assert calculator.SquareRoot(23) == 4.795831523312719
    assert calculator.SquareRoot(947) == 30.773365106858236
    assert calculator.SquareRoot(48.65) == 6.974955196988724
    assert calculator.SquareRoot(1027) == 32.046840717924134
    assert calculator.SquareRoot(19.52) == 4.418144406874904

    # test SquareRoot with 0, which should generate 0
    assert calculator.SquareRoot(0) == 0

    # test SquareRoot with 1, which should generate 1
    assert calculator.SquareRoot(1) == 1

    # test SquareRoot with a negative integer, which should generate an error message
    assert calculator.SquareRoot(-10) == "Cannot get square root of negative numbers"

    # test SquareRoot with a negative floating point value, which should generate an error message
    assert calculator.SquareRoot(-6.897) == "Cannot get square root of negative numbers"

    # Test SquareRoot with edge cases, long integer values, numbers with large number of decimal values
    assert calculator.SquareRoot(2000000000) == 44721.359549995796
    assert calculator.SquareRoot(69000000000) == 262678.510731274
    assert calculator.SquareRoot(0.000000005) == 7.071067811865475e-05
    assert calculator.SquareRoot(500.5000005) == 22.371857332371846
    assert calculator.SquareRoot(80000.00005) == 282.84271256300735


"""*********************************************************************************************************************
***     UNIT TEST FOR X SQUARED
*********************************************************************************************************************"""
def test_xsquared():
    # test the squaring function with basic integer values
    assert calculator.XSquared(2) == 4
    assert calculator.XSquared(3) == 9
    assert calculator.XSquared(4) == 16
    assert calculator.XSquared(50) == 2500
    assert calculator.XSquared(100) == 10000

    # test that a passed 0 returns 0
    assert calculator.XSquared(0) == 0

    # test that a passed 1 returns 1
    assert calculator.XSquared(1) == 1

    # test that a negative passed value ALWAYS returns a positive value
    assert calculator.XSquared(-1) == 1
    assert calculator.XSquared(-2) == 4
    assert calculator.XSquared(-3) == 9
    assert calculator.XSquared(-50) == 2500
    assert calculator.XSquared(-100) == 10000

    # test fractions/floating point values, negative and positive
    assert calculator.XSquared(1.5) == 2.25
    assert calculator.XSquared(-1.5) == 2.25
    assert calculator.XSquared(50.12345) == 2512.3602399025
    assert calculator.XSquared(0.12345) == 0.015239902500000001
    assert calculator.XSquared(-100.987) == 10198.374168999999

    # test edge cases like int min/max, really large/small decimals, etc
    assert calculator.XSquared(20000) == 400000000
    assert calculator.XSquared(-20000) == 400000000
    assert calculator.XSquared(0.000002) == 0.000000000004
    assert calculator.XSquared(0.123456789) == 0.01524157875019052


"""*********************************************************************************************************************
***     UNIT TEST FOR RECIPROCAL
*********************************************************************************************************************"""
def test_reciprocal():
    # Test reciprocal with normal expected integer values
    # Calling the function again on the answer should also return the original value
    assert calculator.Reciprocal(1) == 1
    assert calculator.Reciprocal(8) == 0.125
    assert calculator.Reciprocal(0.125) == 8
    assert calculator.Reciprocal(100) == 0.01
    assert calculator.Reciprocal(0.01) == 100
    assert calculator.Reciprocal(500000) == 0.000002
    assert calculator.Reciprocal(0.000002) == 500000

    # Test reciprocal with negative numbers
    # Calling the function again on the answer should also return the original value
    assert calculator.Reciprocal(-1) == -1
    assert calculator.Reciprocal(-20) == -0.05
    assert calculator.Reciprocal(-0.05) == -20
    assert calculator.Reciprocal(-0.000001) == -1000000
    assert calculator.Reciprocal(-100000) == -0.00001
    assert calculator.Reciprocal(-250000) == -0.000004
    assert calculator.Reciprocal(-0.000004) == -250000

    # Test reciprocal with zero
    # Should issue an error to the user since dividing by zero is not valid
    assert calculator.Reciprocal(0) == "Cannot divide by zero"

    # Test reciprocal with fractions represented as floating point values
    # Calling the function again on the answer should also return the original value
    assert calculator.Reciprocal(0.0000001) == 10000000
    assert calculator.Reciprocal(10000000) == 0.0000001
    assert calculator.Reciprocal(0.00000005) == 20000000
    assert calculator.Reciprocal(200000) == 0.000005

    # Test reciprocal with edge cases
    # Calling the function again on the answer should also return the original value
    assert calculator.Reciprocal(1000000000) == 0.000000001
    assert calculator.Reciprocal(0.0000000001) == 10000000000
    assert calculator.Reciprocal(-1000000000) == -0.000000001
    assert calculator.Reciprocal(-0.0000000001) == -10000000000


"""*********************************************************************************************************************
***     UNIT TEST FOR FACTORIAL
*********************************************************************************************************************"""
def test_factorial():
   # test Factorial with positive integer values
    assert calculator.Factorial(5.0) == 120
    assert calculator.Factorial(
        75.0) == 24809140811395398091946477116594033660926243886570122837795894512655842677572867409443815424000000000000000000
    assert calculator.Factorial(49.0) == 608281864034267560872252163321295376887552831379210240000000000
    assert calculator.Factorial(
        252.0) == 204484624215022882284756162044645354527365854830301974733140854399740327680355894222586710783048275671670129947103938011481584892698594287523178247211816724109883700996451372905507541113381204196195195435460255293477573752210631662539582932406086262252828746817937545830842327002089213302615630504650695790421117659177816706362043873270049714165645369554463748888564282896170368904334765715609531606271737867415895310398229305913612697600000000000000000000000000000000000000000000000000000000000000
    assert calculator.Factorial(
        1523.0) == 648515695001059363556401824805157728597605408529001584706134688154637377194728757491869375321037312151575926258081666424169454971912200681952726234057782033453299705780136739897503731990232825410517603348353494067041241709248447937762684323191389467331697278319694403867269792793150466885338978272726208652503550768528896294750730192171463724852362678924375274838137939174491212427735190186576402549098473556212593087208181899278948108913512547379652854879567576477583151867449704843143407803557909092940232823904355902319520205133061136288858275900607253709801210994727940475604162789582232330626896986508179078142850306546334761725717085812127453347095335141209489454397818538580049451148368031093895589668041484740344595874293907757935182538211344201936830157859081495971533102010426044146706262481823807658199139990592465581591563232256673780062858446890269697301497176102880954776344708277833101693473389441204227443622233963000435334570409446085684068811439041730445216736852730369667336894277734073063869879942633026051828598714693765267101501743853640604747474519436929383806717399334676031694806776151443244363063087462676101877443749568395597543528674394701155586986500240207612267299308501848998359349151304640602953065645323531574530825817925032854203185400486016609210323055180288037297050097727722233657695140706613759227589996275907805256170092059160962278636062514868291356303460798700398622401496554055081750748112356428206356358859602494867165904510736328756008801031958924195875061033084117468945805697099655207526336412323006629941080963328766085360360345874558014994560333046374316747485975064507396196792764079071476693673202647614499717263522718883218253915245995104809303318208524993829149608856962659979671082786697931651611748856413343457609791558625508783839023449761299186803149032126701349916799995463798322603978959700985081586670150732520074739232253420958040958505102203670791225774587036246403272458265726437772902491003573864573300031330793877775144606263718835019766958708956079259447981159036909542895110880867949219885946031246911035273548940458932098496709684061089879099329427876136808009527458714655066958530272690108642315019207271148298530154157675247293336763313191182632482036123155752315098471705289638965450561661906374896698143341667575370936690040054401297087087711108557494370879181840568484073073640272255131417250255595479691993826024137186666451405327552577326442343208942922913702729397223223947064348861756954063837129073210857700113247671042782988176529247227780271545982209379235049279183804796283582365965769395469403354767054763043591609638359236608896705502204257646629488463012974913688149098539911373247368885402942957419155773128249977742340619926548935152515749672854121297653696440467616113485878573023305384252328905700891421158437675426689978290502187314372886603074881427056768423393400524256338605263896419299635241580017725785061049580321531809212056975626334829260947783720107149140504414477401615145630207667416264726150767948742255768734811076824846587330664420904315253709167944986138481196487543188900747525824176317194308974122492139650713638369430051460115009384019330419817503248951527931499436320872813918918931070825995695512058769993314101096787099049012393094652184476218523694731726871523014228213355460888794507979482257038864411956051170492327410611125323070292720406458554434295648270459704304202685113841018897571806812496205270455241603784070738046055144593713894033203182607900740642679198656311368402326390324444854610845484045850715282828278624143833618873778345937561443154649204402938895510458522279640970031567963830624156719751476955315415514720577686188014105571553019679859587440114748105588634202846032193279112789126060517669088448798662243779583651081868286955878209258276835126033248492044250399885283079225344000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

    # test Factorial with 0, which should generate 1
    assert calculator.Factorial(0.0) == 1

    # test Factorial with 1, which should generate 1
    assert calculator.Factorial(1.0) == 1

    # test Factorial with a floating point numbers
    assert calculator.Factorial(6.75) == 3057.822671192606
    assert calculator.Factorial(7.56) == 15903.53764300596
    assert calculator.Factorial(127.89) == 2.2604821502900264e+215
    assert calculator.Factorial(75.849) == 9.796179531198876e+110
    assert calculator.Factorial(58.445) == 1.4397645589453255e+79

    # test Factorial with a negative integer and verify that an error message is generated.
    assert calculator.Factorial(-5.0) == "Cannot get factorial of negative numbers"

    # test Factorial with a negative floating point number and verify that an error message is generated.
    assert calculator.Factorial(-13.8564) == "Cannot get factorial of negative numbers"

    # Test SquareRoot with edge cases
    assert calculator.Factorial(0.12345678) == 0.9423090303920566
    assert calculator.Factorial(105.1234567) == 1.922209391194359e+168
    # assert calculator.Factorial(2000000000) == 50;



"""*********************************************************************************************************************
***     UNIT TEST FOR ABSOLUTE VALUE
*********************************************************************************************************************"""
def test_absolute_value():
    # test the absolute value function with basic integer values
    assert calculator.AbsoluteValue(1) == 1
    assert calculator.AbsoluteValue(2) == 2
    assert calculator.AbsoluteValue(50) == 50
    assert calculator.AbsoluteValue(100) == 100
    assert calculator.AbsoluteValue(1000) == 1000

    # test that a passed 0 returns 0 (which is inherently non-negative)
    assert calculator.AbsoluteValue(0) == 0

    # test that negative numbers are returned as non-negative
    assert calculator.AbsoluteValue(-1) == 1
    assert calculator.AbsoluteValue(-2) == 2
    assert calculator.AbsoluteValue(-50) == 50
    assert calculator.AbsoluteValue(-100) == 100
    assert calculator.AbsoluteValue(-1000) == 1000

    # test fractions/floating-point numbers
    assert calculator.AbsoluteValue(-1.5) == 1.5
    assert calculator.AbsoluteValue(-2.0002) == 2.0002
    assert calculator.AbsoluteValue(50.12345) == 50.12345
    assert calculator.AbsoluteValue(0.100) == 0.100
    assert calculator.AbsoluteValue(-0.001) == 0.001

    # test edge cases, very large/very small values, and positives and negatives
    assert calculator.AbsoluteValue(2147483648) == 2147483648
    assert calculator.AbsoluteValue(2147483648) == 2147483648
    assert calculator.AbsoluteValue(-0.000002) == 0.000002
    assert calculator.AbsoluteValue(0.00000001) == 0.00000001


"""*********************************************************************************************************************
***     UNIT TEST FOR SINE
*********************************************************************************************************************"""
def test_sine():
    # Test sine with normal expected integer values
    assert calculator.Sine(0) == 0
    assert calculator.Sine(90) == 0.8939966636005579
    assert calculator.Sine(180) == -0.8011526357338304
    assert calculator.Sine(55) == -0.9997551733586199
    assert calculator.Sine(-100) == 0.5063656411097588
    assert calculator.Sine(-5) == 0.9589242746631385
    assert calculator.Sine(-200) == 0.8732972972139946
    assert calculator.Sine(3500) == 0.2626657245482294

    # Test sine with fractions represented as floating point values both positive and negative
    assert calculator.Sine(0.15001) == 0.1494480201769065
    assert calculator.Sine(100.12345) == -0.39632897617933605
    assert calculator.Sine(60.34) == -0.6049790705025274
    assert calculator.Sine(-2345.123) == -0.9971197713830722
    assert calculator.Sine(-0.123451) == -0.12313767024099155
    assert calculator.Sine(-40.324) == -0.49401754387979463

    # Test sine with edge cases. Very large positive, negative, and large decimal values
    assert calculator.Sine(-2000000000) == -0.9147104586500817
    assert calculator.Sine(2000000000) == 0.9147104586500817
    assert calculator.Sine(-0.12345678) == -0.1231434062508109
    assert calculator.Sine(-105050.1234567) == -0.9997471024621728


"""*********************************************************************************************************************
***     UNIT TEST FOR COSINE
*********************************************************************************************************************"""
def test_cosine():
    # Test cosine with normal expected integer values
    assert calculator.Cosine(90) == -0.4480736161291701
    assert calculator.Cosine(180) == -0.5984600690578581
    assert calculator.Cosine(55) == 0.022126756261955736
    assert calculator.Cosine(-100) == 0.8623188722876839
    assert calculator.Cosine(-5) == 0.28366218546322625
    assert calculator.Cosine(-200) == 0.48718767500700594
    assert calculator.Cosine(3500) == 0.9648868934479076

    # Test cosine with 0, which should generate 1
    assert calculator.Cosine(0) == 1

    # Test cosine with fractions represented as floating point values both positive and negative
    assert calculator.Cosine(0.15001) == 0.988769583505279
    assert calculator.Cosine(100.12345) == 0.9181085680030654
    assert calculator.Cosine(60.34) == -0.7962413731111302
    assert calculator.Cosine(-2345.123) == 0.0758430057221485
    assert calculator.Cosine(-0.123451) == 0.9923895979743141
    assert calculator.Cosine(-40.324) == -0.8694519344615752

    # Test cosine with edge cases. Very large positive, negative, and large decimal values
    assert calculator.Cosine(-2000000000) == 0.4041098573855347
    assert calculator.Cosine(2000000000) == 0.4041098573855347
    assert calculator.Cosine(-0.12345678) == 0.992388886222003
    assert calculator.Cosine(-105050.1234567) == 0.022488466343654444

