# Rubik's Cube Simulator
Note: Here a lower case letter indicates a counter-clockwise turn

Notation reference: https://en.wikipedia.org/wiki/Rubik's_Cube#Move_notation
### Basic operations
- F (Front): the side currently facing the solver
- B (Back): the side opposite the front
- U (Up): the side above or on top of the front side
- D (Down): the side opposite the top, underneath the Cube
- L (Left): the side directly to the left of the front
- R (Right): the side directly to the right of the front
- X (rotate): rotate the entire Cube on R
- Y (rotate): rotate the entire Cube on U
- Z (rotate): rotate the entire Cube on F

### "MES" extension
- M (Middle): the layer between L and R, turn direction as L (top-down)
- E (Equator): the layer between U and D, turn direction as D (left-right)
- S (Standing): the layer between F and B, turn direction as F

### View tuning
- ( 8 )
- (456): fine tune the view
- 0: reset the view

### Undo and restore
- Q or q: undo
- Hold down Q or q: Keep undoing till it restores
