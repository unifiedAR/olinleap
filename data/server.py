import asyncio
import websockets

async def hello():
    uri = "ws://localhost:57000"
    async with websockets.connect(uri) as websocket:
        res = await websocket.recv()
        print(f"< {res}")

asyncio.get_event_loop().run_until_complete(hello())