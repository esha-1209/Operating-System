import express from 'express'

const app = express()

app.use(express.static('Public'))

app.listen(3000)