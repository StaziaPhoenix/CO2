Welcome to the SIO 190 repository for Spring 2017 at UCSD. Here you will primarily find the work of Team Controller, though we welcome the content from other teams as a central source for documentation, functionality, and eventual release to the public.

For future teams:

You can find our final presentation at https://docs.google.com/presentation/d/1ujXoY42IscQNKDiIRwieQfk2IS0CobTcbv-uFjNDItk/edit?usp=sharing . It outlines our class structure and may help you jump in to using and editing our code.

Essentially, the Analyzer has all objects, including the CLI with which users interact with the system. The benchtop object actuates the flowchart from team benchtop, and receives any object it needs from the analyzer.

We did not have much opportunity to test, so we relied mostly on debug statements to confirm runtime performance. You will likely encounter dissonance between print statements and desired behavior in the hardware - when you experience issues, look there first.

Our Recommendations for Improving the Codebase:

1. You may want to fix the object naming - for example, we have a pinch valve and acid pump which both operate via a relay, so in code we made them both Pinch objects. However, that doesn't functionally make sense, and you may want to make a dedicated acid_pump object (even though it is just a digital pin).
2. Regarding the Pinch Valve: it is not in the final protable system. Instead, according the flowhart from benchtop it uses valves the same way that the syringe pump. However, our quarter did not get that set up, and we have it temporarily operating as a pinch valve in order to work with the hybrid system set up. Depending on how your quarter progresses, you may need to switch it back to a pump object like the control syringe so that you can operate it with valves.


You may contact us at...

Colin Keef        profswirlyeyes@gmail.com
Stazia Tronboll   stazia.phoenix@gmail.com

with questions clarifying our work. Good luck!
