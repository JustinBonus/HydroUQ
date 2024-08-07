# Create ModelBuilder (with two-dimensions and 3 DOF/node)

model basic -ndm 2 -ndf 3

set width    360
set height   144

node  1       0.0     0.0 
node  2    $width     0.0 
node  3       0.0 $height
node  4    $width $height

fix   1     1    1    1
fix   2     1    1    1

# Concrete ( Youngs Modulus, Yield Strength, and Compressive Strength)
pset fc 6.0
pset fy 60.0
pset E 30000.0
uniaxialMaterial Concrete01  1  -$fc  -0.004   -5.0     -0.014
uniaxialMaterial Concrete01  2  -5.0   -0.002   0.0     -0.006

# STEEL
uniaxialMaterial Steel01  3  $fy $E 0.01

set colWidth 15
set colDepth 24 
set cover  1.5
set As    0.60;     # area of no. 7 bars
set y1 [expr $colDepth/2.0]
set z1 [expr $colWidth/2.0]

section Fiber 1 {

    # Create the concrete core fibers
    patch rect 1 10 1 [expr $cover-$y1] [expr $cover-$z1] [expr $y1-$cover] [expr $z1-$cover]

    # Create the concrete cover fibers (top, bottom, left, right)
    patch rect 2 10 1  [expr -$y1] [expr $z1-$cover] $y1 $z1
    patch rect 2 10 1  [expr -$y1] [expr -$z1] $y1 [expr $cover-$z1]
    patch rect 2  2 1  [expr -$y1] [expr $cover-$z1] [expr $cover-$y1] [expr $z1-$cover]
    patch rect 2  2 1  [expr $y1-$cover] [expr $cover-$z1] $y1 [expr $z1-$cover]

    # Create the reinforcing fibers (left, middle, right)
    layer straight 3 3 $As [expr $y1-$cover] [expr $z1-$cover] [expr $y1-$cover] [expr $cover-$z1]
    layer straight 3 2 $As 0.0 [expr $z1-$cover] 0.0 [expr $cover-$z1]
    layer straight 3 3 $As [expr $cover-$y1] [expr $z1-$cover] [expr $cover-$y1] [expr $cover-$z1]

}    


# Define column elements
# ----------------------

# Geometry of column elements
#                tag 

geomTransf Corotational 1  

# Number of integration points along length of element
set np 5

# Create the coulumns using Beam-column elements
#               e            tag ndI ndJ nsecs secID transfTag
set eleType dispBeamColumn
element $eleType  1   1   3   $np    1       1 
element $eleType  2   2   4   $np    1       1 

# Define beam elment
# -----------------------------

# Geometry of column elements
#                tag 
geomTransf Linear 2  

# Create the beam element
#                          tag ndI ndJ     A       E    Iz   transfTag
element elasticBeamColumn   3   3   4    360    4030  8640    2

# Define gravity loads
# --------------------

# Set a parameter for the axial load
set P 180;                # 10% of axial capacity of columns

# Create a Plain load pattern with a Linear TimeSeries
pattern Plain 1 "Linear" {

        # Create nodal loads at nodes 3 & 4
	#    nd    FX          FY  MZ 
	load  3   0.0  [expr -$P] 0.0
	load  4   0.0  [expr -$P] 0.0
}

# ------------------------------
# Start of analysis generation
# ------------------------------

# Create the system of equation, a sparse solver with partial pivoting
system ProfileSPD

# Create the constraint handler, the transformation method
constraints Transformation

# Create the DOF numberer, the reverse Cuthill-McKee algorithm
numberer RCM

# Create the convergence test, the norm of the residual with a tolerance of 
# 1e-12 and a max number of iterations of 10
test NormDispIncr 1.0e-12  10 3

# Create the solution algorithm, a Newton-Raphson algorithm
algorithm Newton

# Create the integration scheme, the LoadControl scheme using steps of 0.1 
integrator LoadControl 0.1

# Create the analysis object
analysis Static

# ------------------------------
# End of analysis generation
# ------------------------------

# perform the gravity load analysis, requires 10 steps to reach the load level
analyze 10

loadConst -time 0.0

# ----------------------------------------------------
# End of Model Generation & Initial Gravity Analysis
# ----------------------------------------------------


# ----------------------------------------------------
# Start of additional modelling for dynamic loads
# ----------------------------------------------------

# Define nodal mass in terms of axial load on columns
set g 386.4
set m [expr $P/$g];       # expr command to evaluate an expression

#    tag   MX   MY   RZ
mass  3    $m   $m    0
mass  4    $m   $m    0
