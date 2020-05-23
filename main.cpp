// main.cpp
//
// ICS 46 Winter 2019
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.

#include "InputReader.hpp"
#include "RoadMapReader.hpp"
#include "TripReader.hpp"
#include "RoadMap.hpp"
#include "RoadMapWriter.hpp"
#include "TripMetric.hpp"
#include "Trip.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>

namespace
{

	std::string getTime(double& seconds, double& total_time)
	{
		std::string output = "";
		total_time += seconds;

		int hours = seconds / 3600;
		if (hours >= 1)
		{
			seconds -= hours * 3600;
			output += std::to_string(hours) + " hours ";

		}

		int minutes = seconds / 60;
		if (minutes >= 1)
		{
			seconds -= minutes * 60;
			output += std::to_string(minutes)  + "minutes ";

		}
		seconds = (int)(seconds * 100) * 0.01;
		output += std::to_string(seconds) + "seconds";
		return output;
		
	}


	void printDistance(const RoadMap& graph, const Trip& trip, const std::function<double(const RoadSegment&)>& fastestTime, const std::map<int, int>& shortest_path, std::vector<std::string>& output)
	{
		int current_vertex = trip.endVertex;
		double vertex_miles = graph.edgeInfo(shortest_path.find(current_vertex)->second, current_vertex).miles;
		double total_miles = 0;

		std::cout << "Shortest distance from " << graph.vertexInfo(trip.startVertex) << " to " << graph.vertexInfo(trip.endVertex) << ":" <<std::endl;
		std::cout << "     Begin at " << graph.vertexInfo(trip.startVertex) << std::endl;
		while(current_vertex != trip.startVertex)
		{
			output.push_back("     Continue to " + graph.vertexInfo(current_vertex) + " (" + std::to_string(vertex_miles) + " miles)");

			current_vertex = shortest_path.find(current_vertex)->second;
			total_miles += vertex_miles;

			if (current_vertex != trip.startVertex)
			{
				vertex_miles = graph.edgeInfo(shortest_path.find(current_vertex)->second, current_vertex).miles;
			}
		}
		for (int i = output.size() - 1; i >= 0; --i)
		{
			std::cout << output[i] << std::endl;
		}
		std::cout << "Total distance: " << total_miles << " miles\n" << std::endl; 

	}

	void printTime(const RoadMap& graph, const Trip& trip, const std::function<double(const RoadSegment&)>& fastestTime, const std::map<int, int>& shortest_path, std::vector<std::string> output)
	{
		int current_vertex = trip.endVertex;
		double vertex_miles = graph.edgeInfo(shortest_path.find(current_vertex)->second, current_vertex).miles;
		double vertex_mph = graph.edgeInfo(shortest_path.find(current_vertex)->second, current_vertex).milesPerHour;
		double total_time = 0;
		double x = vertex_miles / (vertex_mph / 3600);

		std::string time = getTime(x, total_time);
		double total_miles = 0;

		std::cout << "Shortest driving time from " << graph.vertexInfo(trip.startVertex) << " to " << graph.vertexInfo(trip.endVertex) << ":" <<std::endl;
		std::cout << "     Begin at " << graph.vertexInfo(trip.startVertex) << std::endl;

		while(current_vertex != trip.startVertex)
		{
			output.push_back("     Continue to " + graph.vertexInfo(current_vertex) + " (" + std::to_string(vertex_miles) + " miles & " + std::to_string(vertex_mph) + "mph = " + time + ")");

			current_vertex = shortest_path.find(current_vertex)->second;
			total_miles += vertex_miles;

			if (current_vertex != trip.startVertex)
			{
				vertex_miles = graph.edgeInfo(shortest_path.find(current_vertex)->second, current_vertex).miles;
				vertex_mph = graph.edgeInfo(shortest_path.find(current_vertex)->second, current_vertex).milesPerHour;
				x = vertex_miles / (vertex_mph / 3600);
				time = getTime(x, total_time);
			}
		}
		for (int i = output.size() - 1; i >= 0; --i)
		{
			std::cout << output[i] << std::endl;
		}
		total_time /= 2;
		std::cout << "Total time: " << getTime(total_time, total_time) << "\n" << std::endl; 
	}

	void printTripList(const std::vector<Trip>& trip_list, const RoadMap& graph)
	{	
		if (!graph.isStronglyConnected())
		{
			std::cout << "Disconnected Map" << std::endl;
		}
		else
		{
			for (int i = 0; i < trip_list.size(); ++i)
			{
				Trip trip = trip_list[i];
				std::function<double(const RoadSegment&)> fastestTime = [](RoadSegment rs){return rs.miles;};
				std::map<int, int> shortest_path = graph.findShortestPaths(trip.startVertex, fastestTime);
				std::vector<std::string> output;

				if (trip.metric == TripMetric::Distance)
				{
					printDistance(graph, trip, fastestTime, shortest_path, output);
				}
				else if (trip.metric == TripMetric::Time)
				{
					printTime(graph, trip, fastestTime, shortest_path, output);
				}
				else
				{
					std::cout << "Disconnected Map" << std::endl;
				}
			}
		}
	}
}

int main()
{
	InputReader input{std::cin};
	TripReader trip_input;
	RoadMapReader read;
	RoadMap graph = read.readRoadMap(input);

	std::vector<Trip> trip_list = trip_input.readTrips(input);
	printTripList(trip_list, graph);




    return 0;
}

