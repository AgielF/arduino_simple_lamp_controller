const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");
const { Server } = require("socket.io");
const http = require("http");
const express = require("express");

// Initialize express and socket.io
const app = express();
const server = http.createServer(app);
const io = new Server(server);

// Serve static files from the view directory
app.use(express.json());
app.use(express.static(__dirname + "/view"));

// Route to serve the HTML file
app.get("/", (req, res) => {
  res.sendFile(__dirname + "/view/index.html");
});

// Handle socket.io connections
io.on("connection", (socket) => {
  console.log("terhubung...");
  socket.on("disconnect", () => {
    console.log("terputus....");
  });
});

// Start the server
server.listen(3000, () => {
  console.log("server on...");
});

// Configure the serial port
const port = new SerialPort({
  path: "COM4",
  baudRate: 9600,
});

// Error handling for serial port
port.on("error", (err) => {
  console.error("Error opening serial port:", err.message);
  if (err.message.includes("Access denied")) {
    console.error("Akses ke port COM4 ditolak. Pastikan tidak ada aplikasi lain yang menggunakan port ini.");
  }
  // Additional handling like retry logic or notifying the user can be added here
});

// Parse incoming data from the Arduino
const parser = port.pipe(new ReadlineParser({ delimiter: "\r\n" }));

// Handle data received from Arduino
parser.on("data", (result) => {
  console.log("data dari arduino ->", result);
  io.emit("data", { data: result });
});

// Handle data sent to Arduino
app.post("/arduinoAPI", (req, res) => {
  const data = req.body.data;
  port.write(data, (error) => {
    if (error) {
      console.log("errorr...");
      res.status(500).send("Error sending data to Arduino");
    } else {
      console.log("data berhasil dikirim ke arduino data:", data);
      res.send("Data sent to Arduino");
    }
  });
});
