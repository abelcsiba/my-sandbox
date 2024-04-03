FROM node:14 as build 
WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
RUN npm run build
#CMD ["npm", "start"]

FROM nginx:stable-alpine
COPY --from=build /app/build /usr/share/nginx/html
EXPOSE 3000
CMD ["nginx", "-g", "daemon off;"]
