# TravelRecommender
This is a simple module that takes in a timeline of flights schedule and calculates a travel recommendation.

# Flight input has below parameter:
	1)origin,
	2)destination,
	3)departureTime(considered in "minutes since epoch" by the module),
	4)arrivalTime(considered in "minutes since epoch" by the module),
	5)costOfTravel

# recommendation has below parameter:
	1)departureDay(considered in "days since epoch" by the module),
	2)departureTime(considered in "minutes since epoch" by the module),
	3)origin,
	4)destination,
	5)costoftravel,
	6)travelDuration(considered in minutes),
	7)flights(list of flights in order to go from origin to destination)


# user travelling can query by the below parameter:
	1)day of travel,
	2)origin,
	3)destination

and the recommendations that the module is calculating can be used to answer the user query.

# How module calculates the recommendation:
		1)class FlightProcessor takes in all the flights and structure the flights into departure timeline and arrival timeline.
		  departure timeline is a map sorted by departure time and against each departure time there will be a collection of
		  flights departing at that time(at a fixed depart time there can be multiple flights departing from multiple origin city).
		  same can be said about arrival timeline.

		2)FlightProcessor hands over each depart time to class FindRecomendationFromDepTime which calculates all travel solution that starts at this depart time.

		3)class FindRecomendationFromDepTime makes use of class FindRecommendationFromOrigin to find travel solution that starts at origin and we can see
		 that class FindRecomendationFromDepTime can make use of more than one object of FindRecommendationFromOrigin as there can be flights starting at
		 multiple origin city at a depart time.

		4)in order to find travel solutions class FindRecomendationFromDepTime will iterate through all the flights whose travel will end in the next two days
		from the depart time. This is a resonable assumption as we don't want to find travel solution that extends for more than two days. and it helps to
		improve the run time of algorithm. class FindRecomendationFromDepTime passes each flight to class FindRecommendationFromOrigin to find travel
        solution to the destination city of the flight.

		5)once the class FindRecomendationFromDepTime has iterated through all the flights in the next two days from depart time. it collects the travel
		solution from each class FindRecommendationFromOrigin and commences processing for a departure time.

		6) steps 3 to 5 will be done for each depart time in depart timeline.




given origin,destination,departtime,arrivalTime there can be lot of travel paths to go from origin at depart time to destination at arrivalTime. so the best route is the one which is cheapest.
More foramlly we can represent travelSolution as below.

cost = travelSolution(origin, destination, departureTime, arrivalTime)

travelSolution function is what our module does, finds the cheapest route of all possible flight routes that can occur between origin, destination.

lets vary arrival time , let arrival1 < arrival2. we would expect something like below.

(cost1 = travelSolution(origin, destination, departureTime, arrival1)) > ((cost2 = travelSolution(origin, destination, departureTime, arrival2)))

That is if travelDuration increases cost has to be low. If cost is also high and travel duration is also high why to go with this recommendation. So these recommendations are left out by the module.


# complexity:
	each Flight will be considerd once while calculating for each Depart time in minutes by a class FindRecomendationFromDepTime. But the Flight will be considered  	 if it is in the two day range from Depart time. so it can be considerd only for 2880 times(as this many depart times can have a flight in its calculation). in         each Depart time it can be considerd across multiple origin city at that depart time. which can be rounded to a constant C. so overall time complexity will be         (totalFlights * 2880 * C). we can have same number of recommendations(travel solutions) so the space complexity would be the same as well.



# Test case example:

# input:
Flight f1("BLR","DEL",0,3,1);
InFlights.push_back(f1);

Flight f2("ABC","DEL",0,4,2);
InFlights.push_back(f2);

Flight f3("DEL","ABC",38,42,3);
InFlights.push_back(f3);

Flight f4("DEL","ABC",40,42,2);
InFlights.push_back(f4);

Flight f5("DEL","ABC",33,35,2);
InFlights.push_back(f5);

# output:
DepDay(day since epoch) 0
DepMinute(minute since epoch)0
Cost 4
Travel Duration 42
Flight List 1 3
Ori ABC
Dest ABC

DepDay(day since epoch) 0
DepMinute(minute since epoch)0
Cost 2
Travel Duration 4
Flight List 1
Ori ABC
Dest DEL

DepDay(day since epoch) 0
DepMinute(minute since epoch)0
Cost 3
Travel Duration 35
Flight List 0 4
Ori BLR
Dest ABC

DepDay(day since epoch) 0
DepMinute(minute since epoch)0
Cost 1
Travel Duration 3
Flight List 0
Ori BLR
Dest DEL

DepDay(day since epoch) 0
DepMinute(minute since epoch)33
Cost 2
Travel Duration 2
Flight List 4
Ori DEL
Dest ABC

DepDay(day since epoch) 0
DepMinute(minute since epoch)38
Cost 3
Travel Duration 4
Flight List 2
Ori DEL
Dest ABC

DepDay(day since epoch) 0
DepMinute(minute since epoch)40
Cost 2
Travel Duration 2
Flight List 3
Ori DEL
Dest ABC

The flight List in the output recommendation is same as the index of flights in the input vector.


# TODO:
	we can have a file based upload of flights input . we can have a Master service which can take care of uploading the flights to DB and assigning jobs to 	 multiple workers which fetches the  flights from DB and does a recommendation computation and uploads result back to DB. We can expose REST API for fetching
	Recommendation from the system.


