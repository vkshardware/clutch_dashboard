function rotateLeft() {
    backend.to_y_angle = 180
    backend.duration = 2000
    backend.running = true
}


function rotateRight() {
    backend.to_y_angle = -180
    backend.duration = 2000
    backend.running = true
}

function rotateUp() {
    backend.to_x_angle = -180
    backend.model_x_turning.running = true
}


function rotateDown() {
    backend.to_x_angle = 180
    backend.model_x_turning.running = true
}
