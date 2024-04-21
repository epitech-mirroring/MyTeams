#Get fedora base image
FROM fedora:latest

# Install the necessary update
RUN dnf -y update

# Install the necessary packages
RUN dnf -y install gcc make

# copy file to the container
COPY . /root

# run compilation of the project
WORKDIR /root
RUN make prod

#set the env variable for LD_LIBRARY_PATH
ENV LD_LIBRARY_PATH=/root/libs/myteams

#expose the port 8080 for myteams_server app
EXPOSE 8080

#add volume for the data.json file
VOLUME /root/data.json

# run the project
CMD ["./myteams_server", "8080"]

# clen up package cache
RUN dnf clean all

# Add label to the image
LABEL org.opencontainers.image.source https://github.com/epitech-mirroring/MyTeams
LABEL name="Roundtable server"
LABEL description="This a server for myteams project"
