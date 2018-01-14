# 04_BattleTank
Based on UE4 course by Ben Tristem

* Lesson 103
Updated ReadMe file from web based GitHub.

* Lesson 103a
Update on readme file commit from source tree

* Lesson 104
Create Unreal project and tried adding landscape

* Lesson 105
Created a quite large terrain

* Lesson 106
Sculpted mountain barrier / boundary

* Lesson 107
Painted landscape with layered material

* Lesson 108
Created and painted a cell shaded low poly landscape

* Lesson 109
Landscape from heigthmaps import/export

* Lesson 112
Tank creation : fbx import, multimesh assembly, socket positioning

* Lesson 113
Overridden Game Mode and made Tank BP the new default pawn

* Lesson 114
Created buggy input controls for camera rotation

* Lesson 115
Fixed (partially) camera movement by adding a component dedicated to one of the rotations

* Lesson 116
Setup primitive aiming point (Hello world UI)

* Lesson 117
Created main menu as a separate level and set UI in its level blueprint

* Lesson 118
Created font and button for main menu UI

* Lesson 119
Added functionality to Start button, created game quit event, added controller support

* Lesson 120
Game packaging for Win64 and transfer player control from UI to game on menu Start

* Lesson 121
Reparented Tank_BP from Pawn to C++ class Tank derived from Pawn. Same with TankPlayerController_BP from PlayerController to C++ class TankPlayerController

* Lesson 122
Basic code checks that PlayerController controls the correct Pawn

* Lesson 125
Created AI controller class that controls all other tanks (one controller per tank) excluded the player spawned

* Lesson 126
The AI can find which tank is the player's

* Lesson 127
Pseudo code for player aiming inside player controlled tick function

* Lesson 128
Minor code aiming improvement

* Lesson 129
Viewport dimensions and crosshair pixel coordinates

* Lesson 130
DeProjection = ScreenPoint to CameraPosition direction vector

* Lesson 131
LineTrace by Visibility and got HitLocation from Camera Position

* Lesson 132
Get AI and player to call AimAt method of respective Tank class

* Lesson 133
Created C++ component class AimingComponent, attached to actor via C++ (not the editor) and moved aiming debug code there

* Lesson 134
Called C++ function from Tank BP to get ref to Barrel static mesh, passed it to Aiming Component so that it can use it as projectile start position

* Lesson 135
Added variable for projectile speed v0 and prepared to use function for balistic calculation

* Lesson 136
Used helper method to find optimal projectile direction to hit target

* Lesson 137
Created method to rotate barrel towards aim direction

* Lesson 138
Improved code organization using forward declarations

* Lesson 140
Refactored Barrel Static Mesh Component into C++ TankBarrel class and substituted as instance in Tank Blueprint

* Lesson 141
Considered more cafefully which classes should tick and which not. Moved debugging info and discovered bug in trajectory calculation function

* Lesson 142
Fixed trajectory calculation function parameters

* Lesson 143
Rotate barrel mesh if solution found to reach launch direction

* Lesson 145
Made the same as above for the turret

* Lesson 146
Create firing action and projectile C++ Class + BP

* Lesson 150
Used SpawnActor() to spawn projectiles

* Lesson 151
Enable firing on player tank by attaching a existing (Unreal framework) projectile movement component to projectile class

* Lesson 152
Made the AI fire and introduced reload time

* Lesson 153
Discuss the difference between edit anywhere and defauts only

* Lesson 154
Deleted all collision meshes simple and complex on tanks and substituted with a single box in tankBP. Added quit button on main menu

* Lesson 155
Added C++ track class and substituted it to previous static mesh in tankBP. Added left and right throttle controls on mapped to control triggers.

* Lesson 156
Applied force on each track when throttle is pressed to make tank move

* Lesson 157
Override physics material on tracks reducing friction from 0.7 to 0.3

* Lesson 158
Created TankMovementComponent based on NavMovementComponent to drive ranks with left stick or WASD. It also include support for AI patfinding

* Lesson 159
Made the movement component in tankBP visible in BP so that now its methods can be called from blueprint

* Lesson 160
Binded movement component by spawning a reference to it instead of having a pointer in the tank c++ class. Used it to bind both tracks to movement component and wrote code to move forward and backwards