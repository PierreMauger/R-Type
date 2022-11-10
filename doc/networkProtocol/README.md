# <p align="center">🌐 Network protocol</p>

## 👨‍💻 TCP vs UDP

TCP is a connection-oriented network protocol that ensures error checking, order of data transmission and flow/congestion control. It provides reliability when sending data between a server and a single client (for exemple with emails, google searches, downloads...). It however comes with the cost of having longer latency time and consuming more resources (as it has bigger headers on data) compared to UDP which is a message-oriented network protocol that broadcasts the server's data to multiple clients at the same time in services such as streaming or online video games.

Therefore, the use of UDP for in-game communication is appropriate/mandatory for this project and we chose to use TCP for the menu.

## 🎮 Menu and game

As TCP is more reliable, it is used to convey crucial menu informations such as:
- editing a room (create, destroy, set the number of players)
- interacting with a room (player entering, leaving, getting ready, starting the game)
- in-game actions (quitting the game)

On the other hand, UDP in-game data is sent more frequently and can afford having some of it lost (bad internet connection for exemple) when:
- an entity is updated (enemies or players created or destroyed)
- a player input is sent (movement or shooting)

## 📦 Packets

The data is sent by those protocols in packets which form depends on who's sending it (server or client) and for what:
- A "magic number" (just some a few identifying bytes) at the start ensures that the packet's data (at least the start of it) has been sent/received correctly
- A client id if the client is sending it to the server
- A packet type:
    - For the menu:
        - `ROOM_EDIT` Edit a room
        - `ROOM_ACTION` Interact with the room
        - `EVENT` In-game actions
    - For the game:
        - `ENTITY` Entity updated (entity packets are always sent from server to client)
        - `INPUT` Input sent (input packets are always sent from client to server)
- An instruction type:
    - For the menu:
        - For `ROOM_EDIT`:
            - `UPDATE` Update a room (creates it if it doesn't exist)
            - `DESTROY` Destroy a room
        - For `ROOM_ACTION`:
            - `JOIN` Player joins a room
            - `LEAVE` Player leaves a room
            - `READY` Player is ready
            - `UNREADY` Player is not ready
        - For `EVENT`:
            - `GAME_START` Game starts
            - `GAME_END` Game ends
    - For the game:
        - For `ENTITY`
            - `UPDATE` Update a player/enemy (creates it if it doesn't exist)
            - `DESTROY` Destroy a player/enemy
- The actual packet's data, its content depends on the packet and instruction type:
    - For the menu:
        - For `ROOM_EDIT`:
            - For `UPDATE`:
                - The current number of players in the room
                - The max number of players in the room
                - The room id
            - For `DESTROY`:
                - The room id
        - For `ROOM_ACTION`:
            - For `JOIN`:
                - The room id
            - For `LEAVE`:
                - The room id
            - For `READY`:
                - The room id
            - For `UNREADY`:
                - The room id
    - For the game:
        - For `ENTITY`:
            - For `UPDATE`:
                - The entity
            - For `DESTROY`:
                - The entity
        - For `INPUT`:
            - The input key
- The same "magic number" as the start to make sure the whole packet has been sent/received