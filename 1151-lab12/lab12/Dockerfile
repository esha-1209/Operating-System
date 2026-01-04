FROM node:lts-alpine3.23

# copy the files
COPY index.js .
COPY Public ./Public
COPY package.json .

RUN npm install

CMD ["node", "index.js"]
