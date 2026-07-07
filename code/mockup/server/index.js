const { WebSocketServer } = require('ws');
const wss = new WebSocketServer({ port: 8080 }); // Start on port 8080
console.log("SERVER RUNNING!");

let nextId = 0;
const players = new Map();

// const WIDTH = 800, HEIGHT = 800;

// function canSee(id, player) {
//     let curr = players.get(id);
//     return (Math.abs(curr.x - player.x) < WIDTH/2) && (Math.abs(curr.y - player.y) < HEIGHT/2);
// }

wss.on('connection', (ws) => {
    const id = nextId++;
    console.log(`Player ${id} Connected!`);

    players.set(id, {
        x: 0, 
        y: 0,
        ws: ws
    });

    ws.on('message', (data) => {
        const msg = JSON.parse(data.toString());
        players.get(id).x = msg.x;
        players.get(id).y = msg.y;

        for (const [pid, player] of players) {
            const state = {};

            for (const [pid_, player_] of players) {
                // if (pid != pid_ && canSee(pid_, player_)) {
                //     state[pid_] = {
                //         x: player_.x, 
                //         y: player_.y
                //     }
                // }
                if (pid != pid_) {
                    state[pid_] = {
                        x: player_.x, 
                        y: player_.y
                    }
                }
            }

            const packet = JSON.stringify({
                type: 'state', 
                players: state
            });

            if (player.ws.readyState === 1) {
                player.ws.send(packet);
            }
        }
    });
  
    ws.on('close', () => {
        players.delete(id);
        console.log(`Player ${id} disconnected`);
    });
});