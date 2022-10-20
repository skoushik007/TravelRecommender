# TravelRecommender
This is a simple module that takes in a timeline of flights schedule and calculates a travel recommendation.

a Flight input has below parameter:
	origin	
	destination	
	departureTime(considered in "minutes since epoch" by the module)	
	arrivalTime(considered in "minutes since epoch" by the module)	
	costOfTravel	

a recommendation has below parameter:
	departureDay(considered in "days since epoch" by the module)
	departureTime(considered in "minutes since epoch" by the module)
	origin
	destination
	costoftravel
	travelDuration(considered in minutes)
	flights(list of flights in order to go from origin to destination)


ideally the user travelling will query by the below parameter:
	day of travel
	origin
	destination

and the recommendation that the module is calculating can be used to answer the user query.

How module calculates the recommendation:
		1)class FlightProcessor takes in all the flights and structure the flights into departure timeline and arrival timeline. 
		  departure timeline is a map sorted by departure time and against each departure time there will be a collection of 
		  flights departing at that time(at a fixed depart time there can be multiple flights departing from multiple origin city).same can be said about     			arrival timeline.
		
		2)FlightProcessor hands over each depart time to class FindRecomendationFromDepTime which calculates all travel solution that starts at this depart 		     time.
		
		3)class FindRecomendationFromDepTime makes use of class FindRecommendationFromOrigin to find travel solution that starts at origin and we can see
		 that class FindRecomendationFromDepTime can make use of more than one object of FindRecommendationFromOrigin as there can be flights starting at 		   multiple origin city at a depart time.
		 
		4)in order to find travel solutions class FindRecomendationFromDepTime will iterate through all the flights whose travel will end in the next two days 			 from the depart time. This is a resonable assumption as we don't want to find travel solution that extends for more than two days. and it helps to 		      improve the run time of algorithm. class FindRecomendationFromDepTime passes each flight to class FindRecommendationFromOrigin to find travel 			  solution to the destination city of the flight.
		
		5)once the class FindRecomendationFromDepTime has iterated through all the flights in the next two days from depart time. it collects the travel 		   solution from each class FindRecommendationFromOrigin and commences processing for a departure time.
		 
		6) steps 3 to 5 will be done for each depart time in depart timeline.
		



given origin,destination,departtime,arrivalTime there can be lot of travel paths to go from origin at depart time to destination at arrivalTime. so the best route is the one which is cheapest.
More foramlly we can represent travelSolution as below.

cost = travelSolution(origin, destination, departureTime, arrivalTime)

travelSolution function is what our module does, finds the cheapest route of all possible flight routes.
 
lets vary arrival time , let arrival1 < arrival2. we would expect something like below.

(cost1 = travelSolution(origin, destination, departureTime, arrival1)) > ((cost2 = travelSolution(origin, destination, departureTime, arrival2)))

That is if travelDuration increases cost has to be low. If cost is also high and travel duration is also high why to go with this recommendation. So these recommendations are left out by the module.


complexity:
	each Flight can be considerd once while calculating for each Depart time in minutes by a class FindRecomendationFromDepTime. But the Flight will be considered  	if it is in the two day range from Depart time. so it can be considerd only for 2880 times(as this many depart times can have a flight in its calculation). in         each Depart time it can be considerd across multiple origin city at that depart time. which can be rounded to a constant C. 
	so overall time complexity will be (totalFlights*2880*C). we can have same number of recommendations(travel solutions) so the space complexity would be the      	 same as well.



