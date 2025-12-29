# Qt Telemetry Dashboard

Qt Telemetry Dashboard is a feature-complete Qt 6 application built with a QML frontend and a C++ application/service layer.
The app connects to a WebSocket server (local or remote), receives live JSON telemetry messages, processes them in C++, and
presents them in a responsive, data-driven UI.

## Screenshot

![Screenshot](docs/screenshots/app-screenshot.png)

## Features

- Qt 6.10
- Qt Quick + QML UI
- Live WebSocket connection using QWebSocket
- Real-time telemetry feed parsed and validated in C++
- QAbstractListModel exposing structured data to QML
- Centralized application state via Q_PROPERTY
- Clean separation of concerns:
    - No networking or business logic in QML
    - UI reacts purely to state and models
- Graceful handling of:
    - Connection states
    - Loading states
    - Errors and disconnects
- CMake build system
- Keyboard shortcuts
    - `Esc` to quit
    - `Alt + Enter` to toggle fullscreen

## Project Structure

```bash

qt-telemetry-dashboard/
│
├──src/
│   ├── app/
│   │   ├── AppController.h / .cpp
│   │   └── AppState.h / .cpp
│   │
│   ├── models/
│   │   ├── TelemetryItem.h
│   │   └── TelemetryModel.h / .cpp
│   │
│   ├── services/
│   │   ├── TelemetryService.h / .cpp
│   │   └── ConnectionService.h / .cpp
│   │
│   ├── workers/
│   │   └── TelemetryWorker.h / .cpp
│   │
│   ├── utils/
│   │   └── Logger.h / .cpp
│   │
│   └── main.cpp
│
├── qml/
│   │
│   ├── screens/
│   │   ├── DashboardScreen.qml
│   │   └── ErrorScreen.qml
│   │
│   ├── components/
│   │   ├── TelemetryCard.qml
│   │   └── StatusBar.qml
│   │
│   └── main.qml
│
├── echo-server.js
├── CMakeLists.txt
├── README.md
└── docs/
    └── screenshots/
```

## Key Components

### AppController

- Orchestrates services, models, and state
- Exposed to QML as the single interaction point

### AppState

- Holds global UI state (`loading`, `connected`, `errorMessage`)

### TelemetryService

- Manages WebSocket lifecycle
- Parses incoming JSON messages
- Sends test telemetry messages when using an echo server

### QML

- Declarative UI only
- No networking or parsing logic

## WebSocket Backend

The app can connect to:

1. Local test server (recommended for development):
    - Node.js WebSocket echo server:
```bash
npm install ws
node echo-server.js
```
- Server listens at ws://localhost:8080
- Example message format:
```json
{
  "id": "sensor-17",
  "timestamp": 1735234241,
  "type": "temperature",
  "value": 72.4,
  "status": "ok"
}
```
- TelemetryService sends test messages to the echo server and displays them in the UI.
2. Remote servers:
    - Any WebSocket server that sends JSON telemetry messages in the above format.
    - The URL can be passed to `AppController.connectToServer("ws://<host>:<port>")`.

## Getting Started

**Prerequisites**
- Qt 6.x with QtQuick, QtQuick.Controls, and QtQuick.Layouts
- C++17 or newer
- CMake (if building with CMake) or Qt Creator

**Build Instructions**
1. Clone the repository:
```bash
git clone https://github.com/dtb1996/qt-telemetry-dashboard.git
cd qt-telemetry-dashboard
```
2. Open the project in Qt Creator:
    - `File → Open File or Project → select CMakeLists.txt`
3. Build and run the project.

### Echo Server Setup

#### Install Node.js

**Linux (Ubuntu/Debian)**
```bash
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt-get install -y nodejs
```

**macOS (Homebrew)**
```bash
brew install node@18
```

**Windows**
- Download the installer from Node.js official site and run it.

Check installation:
```bash
node -v
npm -v
```

#### Run the Local Echo Server

1. Navigate to the project folder (or create a /tools folder in the repo) and save the server as echo-server.js:
```js
const WebSocket = require('ws');

const port = 8080;
const wss = new WebSocket.Server({ port });

wss.on('connection', ws => {
    console.log('Client connected');
    ws.on('message', message => {
        console.log('Received:', message.toString());
        ws.send(message.toString()); // Echo it back
    });
    ws.on('close', () => console.log('Client disconnected'));
});

console.log(`WebSocket echo server running at ws://localhost:${port}`);
```

2. Install dependencies:
```bash
cd tools
npm install ws
```

3. Start the server:
```bash
node echo-server.js
```

4. You should see:
```bash
WebSocket echo server running at ws://localhost:8080
```

5. In the Qt Telemetry Dashboard UI, click Connect to connect to the local server. The telemetry messages will be sent,
echoed back, and displayed in the UI.

## Purpose of the Project

This project demonstrates:
- Real-world Qt/C++ patterns used in production
- Clean separation between UI and logic
- Strong typing across C++ and QML
- Model-driven UI updates
- Practical WebSocket integration
