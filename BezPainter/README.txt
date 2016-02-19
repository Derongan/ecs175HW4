David Friedman
#998881687

This is a bezier painter.

It supports saving, maintains continuity, and allows adding of lines as well as bezier curves.

The included save file draws two sets of curves. One with 5 or so curves of degree 3 with c1 continuity, and a bunch more above with varying degrees.

IMPORTANT NOTE:
	There is a bug where if you right click near the edge of the window, then do anything but choose a color the program crashes. I don't know why and tracing only leads me into GLUT code.
IMPORTANT NOTE2:
	This program is by no means memory efficient. I tried to clean up data as best I could but I definately missed a few objects. Expect long use to cause lots of memory to be eaten.

The menu system is simple. Right click to see available tools and commands.

1. Finish Curve
	Finish a curve early before you hit the MAXPOINTS allowed for a curve
2. Point
	Switch to the point tool. The point tool has undefined behaviour when saving/loading. I'd suggest not using it in general.
3. Line
	A straight line between two points. Snaps to control points slightly.
4. Curve
	The bezier curve tool. Maintains C1 continuity in most cases (if you connect curves of order 3 at two points it does not guarantee continuity on both sides)
5. Select
	Used for selecting curves/lines and modifying their control points. Maintains continuity for curves.
6. -----
	I don't know how to add breaks so this is a nonfunctioning button meant to seperate two groups
7. Save
	Save to saved_data.bez
8. Load
	Load from saved_data.bez
9. Reset
	Resets the current canvas. Does not perform memory cleanup, so prepare for saddness if used too much
10. Color
	Select a color using this and its submenu from a wide array of 3 choices, RED, BLUE, and GREEN!