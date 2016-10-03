#ifndef RUNWAY
#define RUNWAY
#include "Plane.cpp"
#include "Extended_queue.cpp"
#include "utility.cpp"
#include <queue>

using namespace std;
enum Runway_activity {idle, land, takeoff};

 class Runway {
public:
Runway(int limit);
Error_code can_land(const Plane &current);
Error_code can_depart(const Plane &current);
Runway_activity activity(int time, Plane &moving);
void shut_down(int time) const;
private:
Extended_queue landing;
Extended_queue takeoff;
int queue_limit;
int num_land_requests; // number of planes asking to land
int num_takeoff_requests; // number of planes asking to take off
int num_landings; // number of planes that have landed
int num_takeoffs; // number of planes that have taken off
int num_land_accepted; // number of planes queued to land
int num_takeoff_accepted; // number of planes queued to take off
int num_land_refused; // number of landing planes refused
int num_takeoff_refused; // number of departing planes refused
int land_wait; // total time of planes waiting to land
int takeoff_wait; // total time of planes waiting to take off
int idle_time; // total time runway is idle
};


Runway::Runway(int limit)
/* Post: The Runway data members are initialized to record no prior Runway use
and to record the limit on queue sizes. */
{
queue_limit = limit;
num_land_requests = num_takeoff_requests = 0;
num_landings = num_takeoffs = 0;
num_land_refused = num_takeoff_refused = 0;
num_land_accepted = num_takeoff_accepted = 0;
land_wait = takeoff_wait = idle_time = 0;
}


//  can_land  &　can_depart:  控制飞机加入对应队列
Error_code Runway::can_land(const Plane &current)
/* Post: If possible, the Plane current is added to the landing Queue; otherwise,
an Error_code of overflow is returned. The Runway statistics are updated.
Uses: class Extended_queue. */
{
	Error_code result;
		if (landing.size( ) < queue_limit)
		result = landing.append(current);
		else
		result = fail;
		num_land_requests++;
	if (result != success){ 
	num_land_refused++;}
	else
	num_land_accepted++;
	return result;
}
Error_code Runway::can_depart(const Plane &current)
/* Post: If possible, the Plane current is added to the takeoff Queue; otherwise, an
Error_code of overflow is returned. The Runway statistics are updated.
Uses: class Extended_queue. */
{
Error_code result;
if (takeoff.size( ) < queue_limit)
result = takeoff.append(current);
else
result = fail;
num_takeoff_requests++;

if (result != success)
num_takeoff_refused++;
else
num_takeoff_accepted++;
return result;
}

Runway_activity Runway::activity(int time, Plane &moving)
/* Post: If the landing Queue has entries, its front Plane is copied to the parameter
moving and a result land is returned. Otherwise, if the takeoff Queue has
entries, its front Plane is copied to the parameter moving and a result
takeoff is returned. Otherwise, idle is returned. Runway statistics are
updated.
Uses: class Extended_queue. */
{
Runway_activity in_progress; 
if (!landing.empty( )) {
landing.retrieve(moving);
land_wait += time - moving.started( );
num_landings++;
in_progress = land;
landing.serve( );
}
else if (!takeoff.empty( )) {
takeoff.retrieve(moving);
takeoff_wait += time - moving.started( );
num_takeoffs++;
in_progress = (Runway_activity)2; // type Runway_activity "takeoff" equals 2 
takeoff.serve( );
}
else {
idle_time++;
in_progress = idle;
}
return in_progress;
}

void Runway::shut_down(int time) const
/* Post: Runway usage statistics are summarized and printed. */
{
cout << "Simulation has concluded after " << time << " time units." << endl
<< "Total number of planes processed "
<< (num_land_requests + num_takeoff_requests) << endl
<< "Total number of planes asking to land "
<< num_land_requests << endl
<< "Total number of planes asking to take off "
<< num_takeoff_requests << endl
<< "Total number of planes accepted for landing "
<< num_land_accepted << endl
<< "Total number of planes accepted for takeoff "
<< num_takeoff_accepted << endl
<< "Total number of planes refused for landing "
<< num_land_refused << endl
<< "Total number of planes refused for takeoff "
<< num_takeoff_refused << endl
<< "Total number of planes that landed "
<< num_landings << endl
<< "Total number of planes that took off "
<< num_takeoffs << endl
<< "Total number of planes left in landing queue "
<< landing.size( ) << endl
<< "Total number of planes left in takeoff queue "
<< takeoff.size( ) << endl;
cout << "Percentage of time runway idle "
<< 100.0 * ((float) idle_time)/((float) time) << "%" << endl;
cout << "Average wait in landing queue "
<< ((float) land_wait)/((float) num_landings) << " time units";
cout << endl << "Average wait in takeoff queue "
<< ((float) takeoff_wait)/((float) num_takeoffs)
<< " time units" << endl;
cout << "Average observed rate of planes wanting to land "
<< ((float) num_land_requests)/((float) time)
<< " per time unit" << endl;
cout << "Average observed rate of planes wanting to take off "
<< ((float) num_takeoff_requests)/((float) time)
<< " per time unit" << endl;
}
#endif
