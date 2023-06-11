// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlideGameEditor.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FSlideGameEditorModule, SlideGameEditor );

DEFINE_LOG_CATEGORY(LogSlideGameEditor)


#define LOCTEXT_NAMESPACE "SlideGameEditor"

void FSlideGameEditorModule::StartupModule()
{
    UE_LOG(LogSlideGameEditor, Warning, TEXT("SlideGameEditor: Log Started"));
}

void FSlideGameEditorModule::ShutdownModule()
{
    UE_LOG(LogSlideGameEditor, Warning, TEXT("SlideGameEditor: Log Ended"));
}

#undef LOCTEXT_NAMESPACE