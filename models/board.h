int boardVertexCount=36;

        float boardVertices[]={
                1.0f,-1.0f,-1.0f,1.0f,
                -1.0f, 1.0f,-1.0f,1.0f,
                -1.0f,-1.0f,-1.0f,1.0f,

                1.0f,-1.0f,-1.0f,1.0f,
                1.0f, 1.0f,-1.0f,1.0f,
                -1.0f, 1.0f,-1.0f,1.0f,


                -1.0f,-1.0f, 1.0f,1.0f,
                1.0f, 1.0f, 1.0f,1.0f,
                1.0f,-1.0f, 1.0f,1.0f,

                -1.0f,-1.0f, 1.0f,1.0f,
                -1.0f, 1.0f, 1.0f,1.0f,
                1.0f, 1.0f, 1.0f,1.0f,

                1.0f,-1.0f, 1.0f,1.0f,
                1.0f, 1.0f,-1.0f,1.0f,
                1.0f,-1.0f,-1.0f,1.0f,

                1.0f,-1.0f, 1.0f,1.0f,
                1.0f, 1.0f, 1.0f,1.0f,
                1.0f, 1.0f,-1.0f,1.0f,

                -1.0f,-1.0f,-1.0f,1.0f,
                -1.0f, 1.0f, 1.0f,1.0f,
                -1.0f,-1.0f, 1.0f,1.0f,

                -1.0f,-1.0f,-1.0f,1.0f,
                -1.0f, 1.0f,-1.0f,1.0f,
                -1.0f, 1.0f, 1.0f,1.0f,

                -1.0f,-1.0f,-1.0f,1.0f,
                1.0f,-1.0f, 1.0f,1.0f,
                1.0f,-1.0f,-1.0f,1.0f,

                -1.0f,-1.0f,-1.0f,1.0f,
                -1.0f,-1.0f, 1.0f,1.0f,
                1.0f,-1.0f, 1.0f,1.0f,

                -1.0f, 1.0f, 1.0f,1.0f,
                1.0f, 1.0f,-1.0f,1.0f,
                1.0f, 1.0f, 1.0f,1.0f,

                -1.0f, 1.0f, 1.0f,1.0f,
                -1.0f, 1.0f,-1.0f,1.0f,
                1.0f, 1.0f,-1.0f,1.0f,

        };


        float boardNormals[]={
                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,

                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,

                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,

                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,

                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,

                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,

                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,

                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,

                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,

                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,
                0.0f, 0.0f,-1.0f,0.0f,

                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,

                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,
                0.0f, 0.0f, -1.0f,0.0f,
        };


        float boardTexCoords[]={
                1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
                1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

                1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
                1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

                1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
                1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

                1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
                1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

                1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
                1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

                1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
                1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
        };
