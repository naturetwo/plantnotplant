<!---
[![banner](https://raw.githubusercontent.com/link.png)](https://link.com)
--->

# 🌱  plantnotplant 🍂 plant classification subsystem

>    Plant classification subsystem, hacking towards an automous AI rover hardware and software platform classify plants!
<!---
>    [org](https://link.com) (add n2 link)
--->


<!---
TODO Change this to match the repo name and testing environments
[![Travis (.com)](https://img.shields.io/travis/com/link.svg)](https://travis-ci.com/orglink)
[![Codacy coverage](https://img.shields.io/codacy/coverage/link.svg)](https://app.codacy.com/project/orglink)
[![PyPI](https://img.shields.io/pypi/v/link.svg)](https://pypi.org/project/orglink/)
[![GitHub contributors](https://img.shields.io/github/contributors/link.svg)](https://github.com/oceanprotocol/orglink/contributors)
--->

## Research plan:

1) Deep learning pipeline for state transitions
  - Recognize center of plant and perform classificaiton
  - Recognize end of track without relying on hardware
2) Deep learning pipeline for data labeling
  - From hand-written label, recognize species of plant
  - From hand-written label, apply data labels 
     - Height of plant
     - Number of plants
     - ?? 
3) Deep learning classification
  - Collect N camera positions at a single plant
  - Is 3D CNN better, or just a single position? 

### Botony: 
#### Ocimum × africanum, (Thai Basil)
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/97/Kemangi.jpg/450px-Kemangi.jpg" height="200" width="170">

#### Origanum vulgare (Oregano)
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/51/Dobromysl_obecn%C3%A1.jpg/675px-Dobromysl_obecn%C3%A1.jpg" height="200" width="170">

### Hardware:
2) Rasperry-pi as master
  - Camera: Night / Standard / Fisheye?
  - Python stack
  - Keras/Tensorflow
  - Open CV
  
1) 2-axis mounted camera controlled by Arduino
  - Stepper motor for linear
  - Servo for camera scanning

```
Motor 1.7 A / stage

DRV 8825 max continuous current: 1.5 A

Target current: 1.3 A (derated)

VREF = Current limit / 2 = 0.65V

SEE: https://forum.arduino.cc/index.php?topic=415724.0
```


### Software:
3D CNN

---

## Table of Contents

  - [Features](#features)
  - [Prerequisites](#prerequisites)
  - [Quickstart](#quickstart)
  - [Environment variables](#environment-variables)
  - [Code style](#code-style)
  - [Testing](#testing)
  - [New Version](#new-version)
  - [License](#license)

---


## Features

TODO

## Prerequisites

TODO


## Quickstart

...


## Environment variables

TODO


...

## Code style

.
​    
## Testing

Automatic tests are setup via Travis, executing `tox`.
Our test use pytest framework.

## New Version

The `bumpversion.sh` script helps to bump the project version. You can execute the script using as first argument {major|minor|patch} to bump accordingly the version.

## License

```
todo

```
