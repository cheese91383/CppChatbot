document.querySelector('.chat-form').addEventListener('submit', async (e) => {
    e.preventDefault();
    const input = document.querySelector('.chat-form input');
    const userMessage = input.value;
    const payload = {
        user_id: 'user1', // Replace with actual user data if available
        message: userMessage
    };

    try {
        const response = await fetch('/api/chat', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(payload)
        });

        const data = await response.json();
        // Here you would inject the backend response into your chat area
        console.log(data);
        // For example, append the response to your chat messages container:
        const chatMessagesDiv = document.querySelector('.chat-messages');
        const messageElement = document.createElement('div');
        messageElement.className = 'message received';
        messageElement.innerHTML = `<p>${data.message}</p><span class="time">${new Date().toLocaleTimeString()}</span>`;
        chatMessagesDiv.appendChild(messageElement);
    } catch (error) {
        console.error('Error fetching chat response:', error);
    }
    input.value = ''; // Clear input field after sending
});
