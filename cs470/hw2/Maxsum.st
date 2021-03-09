Object subclass: #ParkMillerRNG
    instanceVariableNames: 'seed'
    classVariableNames: 'PMa PMm PMmu1 PMq PMr'
    poolDictionaries: '' 
    category: nil !

ParkMillerRNG comment: 'I implement Park/Miller random number generation' !

!ParkMillerRNG class methodsFor: 'initialization'!
initialize
    PMa := 16r00041A7.
    PMm := 16r7FFFFFF.
    PMq := 16r001F31D.
    PMr := 16r0000B14.
    PMmu1 := 0.46566128752457969e-9.
!!

!ParkMillerRNG class methodsFor: 'creating RNG instances'!
new
    self initialize.
    ^ super new initialize 
!!

!ParkMillerRNG methodsFor: 'initializing starting seed'!
initialize
    " Set a reasonable Park-Miller random starting seed "
    seed := 45678901
!!

!ParkMillerRNG methodsFor: 'next random float between 0.0 and 1.0'!
next
    seed := self peekInteger.
    ^ seed * PMmu1
!!

!ParkMillerRNG methodsFor: 'next random integer between 0 and 16r7FFFFFFF'!
nextInteger
    seed := self peekInteger.
    ^ seed
!!

!ParkMillerRNG methodsFor: 'peek at next float'!
peek
    ^ self peekInteger * PMmu1
!!

!ParkMillerRNG methodsFor: 'peek at next integer'!
peekInteger
    | lo hi aLoRHi answer |
    hi := seed quo: PMq.
    lo := seed rem: PMq.
    aLoRHi := (PMa * lo) - (PMr * hi).
    answer := (aLoRHi > 0)
	ifTrue: [ ^ aLoRHi ].
    ^ aLoRHi + PMm
!!

!ParkMillerRNG methodsFor: 'seed the RNG'!
seed: anInteger
     seed := anInteger
!!


"***************************************************************"
"***************************************************************"
"Parker Johnson							"
"CS470  3-25-98							"
"Maxsum.st							"
"This code was written by me and me only  -parker johnson	"
"***************************************************************"
"***************************************************************"

"Myarray is a subclass of Object.  It contains two variables	"
"sarray and rng.  sarray will be initialized to be bound to an	"
"array which is already built into the pre-existing heirarchy	"
"rng is a varaible which will be bound to a random number object"



Object subclass: #Myarray
     instanceVariableNames: 'sarray rng'
     classVariableNames: ''
     poolDictionaries: ''
     category: nil !

"This is the comment for Myarray"

Myarray comment: 'This is an array to be filled with rand numbers' !

!Myarray class methodsFor: 'instance creation'!
new

     | r |		"This is the Myarray new method, here 	"
			"Object creates the Myarray object then	"
     r:= super new.	"the initialization routine is called on"
     r init.		"r and then finally returned.  This is	"
     ^ r.		"similar to the constructor in C++	"

!!


!Myarray methodsFor: 'instance initialization'!
init

     sarray:=Array new: 20.	"this is the initialization routine"
     rng:=ParkMillerRNG new.	"then a loop is used to initialize "
     				"the array w/ -100<nums<100	   "

     1 to: 20 do: [:ii| sarray at: ii put: ((rng nextInteger)rem: 100)].

!!


!Myarray methodsFor: 'printing'!	"this is the print routine"
printOn: aStream
     super printOn: aStream.
     'sarray has contents' printOn: aStream.
     sarray printOn: aStream.
!!




"******************************************************************"

"This object Maxsum is a subclass of Myarray.  The reason being	"
"is that it need to inherit the sarray found in Myarray.  	"
"There is only one instance variable, max.  max stores the	"
"maximum sum of the subsequence in sarray.  Because it is only	"
"used in the Maxsum method compute, it could have been declared	"
"locally to that method.  I declared it as a private member to	"
"be consistent with the themes of o-o programming.		"


Myarray subclass: #Maxsum
     instanceVariableNames: 'max start end'
     classVariableNames: ''
     poolDictionaries: ''
     category: nil !  

"here is my Maxsum comment"

Maxsum comment: 'This object computes the Maxsum of a sequence' !

!Maxsum class methodsFor: 'instance creation'!
new

     | s |		"This is the Maxsum new method, here    "
			"Myarray creates the Maxsum object then "
     s:= super new.	"the initialization routine is called on"
     s init.		"s and then finally returned.  This is  "
     ^ s.		"similar to the constructor in C++      "

!!


!Maxsum methodsFor: 'instance initialization'!
init
     
     max:= 0.		"This is actually trivial"
     ^ super init.	"This is crucial to initializing the	"
			"parent object.  Maxsum needs to do this"
!!			"to have the sarray.			"


!Maxsum methodsFor: 'compute the Maxsum'!  
compute

     | ii jj kk this |		"this nasty chunck of code finds"
                       		"the maximimum sum and sets the	"
     ii:=0. max:=0. this:= 0.	"indices of the sarray.  Start	"
				"points to the start of the seq "
				"and end to the end of the seq.	"

     1 to: 20 do: [:ii| jj := ii.
	jj to: 20 do: [:jj | this:= 0. kk := ii.
	    kk to: jj do: [:kk | this := (this + (sarray at: kk)) ].

            (this > max) ifTrue: [  max := this. start:= ii. end:=jj ].  
		      ].
		  ].

      ^ max.
!!


!Maxsum methodsFor: 'printing'!
printOn: aStream
     				"this is the print method for the"
				"Maxsum object.  It uses the vars"
				"sarray, which it inherits from	 "
				"parent, and the subclass vars	 "
				"start, end, and maxsum		 "

     ('The Sequence Generated Is:') printNl.
     1 to: 20 do: [:ii| (sarray at: ii) print. ' ' print. ].
     ('') printNl.
     ('Max Subsequence is:') printNl.
     start to: end do: [:ii| (sarray at: ii) print. ' ' print. ].
     ('') printNl.
     'Maxsum is ' printOn: aStream.
     max printOn: aStream.
!!



