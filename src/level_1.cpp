void level_1(float gameSpeed, Texture2D background, Texture2D midLayer, Texture2D foreLayer) {
    //Load textures for background layers
    background = LoadTexture("assets/backgrounds/bg1.png");
    midLayer = LoadTexture("assets/backgrounds/ol1.png");
    foreLayer = LoadTexture("assets/backgrounds/ol4.png");

    float bgScroll = 0;
    float midScroll = -midLayer.height*2;
    float foreScroll = -foreLayer.height*2;

    //Game loop
    while (!WindowShouldClose())
    {
        //Update background positions
        bgScroll += 5.0f * gameSpeed;
        midScroll += 10.0f * gameSpeed;
        foreScroll += 7.5f * gameSpeed;


        //Reset background position to loop
        if (bgScroll >= background.height*2) bgScroll = 0;
        if (midScroll >= midLayer.height*2) midScroll = -midLayer.height*2;
        if (foreScroll >= foreLayer.height*2) foreScroll = -foreLayer.height*2;

        BeginDrawing();
            ClearBackground(BLACK);

            //Draw backgrounds based on positions being updated
            DrawTextureEx(background, (Vector2){ 0, bgScroll}, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ 0, -background.height*2 + bgScroll }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midLayer, (Vector2){ 0, midScroll }, 0.0f, 1.0f, WHITE);
            DrawTextureEx(midLayer, (Vector2){ 0, -midLayer.height + midScroll }, 0.0f, 1.0f, WHITE);
            DrawTextureEx(foreLayer, (Vector2){ 0, foreScroll }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreLayer, (Vector2){ 0, -foreLayer.height + foreScroll }, 0.0f, 2.0f, WHITE);

            
            DrawFPS(10,10);
        EndDrawing();
    }
}