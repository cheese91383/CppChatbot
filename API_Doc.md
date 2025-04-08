Backend port: 53241

format: json

example chatting:
```json
{
    "user_id": "user1",
    "message": "Hello {robot_name}, how are you?"
}
```
```json
{
    "message": "Hello user1, I'm fine, how can I help you?"
}
```

code: 500
```json
{
    "message": "Server error"
}
```



{robot_name}