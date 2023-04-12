#include "MenuButton.hpp"
#include "Game.hpp"

MenuButton::MenuButton(Game* game, Type type, State start) : SceneNode(game)
{
	currentState = start;

	switch (type) {
	case Play:
		mSprite = "PlayUnSelected";
		mAltSprite = "PlaySelected";
		break;
	case Quit:
		mSprite = "QuitUnSelected";
		mAltSprite = "QuitSelected";
		break;
	}
}

void MenuButton::switchState()
{
	if (currentState == UnSelected) {
		currentState = Selected;
		return;
	}

	currentState = UnSelected;
}

void MenuButton::updateCurrent(const GameTimer& gt)
{
}

void MenuButton::drawCurrent(RenderContext context) const
{
	RenderItem* renderToUse = nullptr;

	if (currentState == UnSelected) {
		renderToUse = renderer;
	}
	else
	{
		renderToUse = altRenderer;
	}

	renderToUse->World = getTransform();
	renderToUse->NumFramesDirty++;

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = context.mCurrFrameResource->ObjectCB->Resource();
	auto matCB = context.mCurrFrameResource->MaterialCB->Resource();

	context.cmdList->IASetVertexBuffers(0, 1, &renderToUse->Geo->VertexBufferView());
	context.cmdList->IASetIndexBuffer(&renderToUse->Geo->IndexBufferView());
	context.cmdList->IASetPrimitiveTopology(renderToUse->PrimitiveType);

	//step18
	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(context.mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
	tex.Offset(renderToUse->Mat->DiffuseSrvHeapIndex, context.mCbvSrvDescriptorSize);

	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + renderToUse->ObjCBIndex * objCBByteSize;
	D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + renderToUse->Mat->MatCBIndex * matCBByteSize;

	//step19
	context.cmdList->SetGraphicsRootDescriptorTable(0, tex);
	context.cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
	context.cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

	context.cmdList->DrawIndexedInstanced(renderToUse->IndexCount, 1, renderToUse->StartIndexLocation, renderToUse->BaseVertexLocation, 0);
}

void MenuButton::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["Menu"].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));

	auto altRender = std::make_unique<RenderItem>();
	altRenderer = render.get();
	altRenderer->World = getTransform();
	XMStoreFloat4x4(&altRenderer->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	altRenderer->ObjCBIndex = game->getRenderItems().size();
	altRenderer->Mat = game->getMaterials()["Menu"].get();
	altRenderer->Geo = game->getGeometries()["boxGeo"].get();
	altRenderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	altRenderer->IndexCount = altRenderer->Geo->DrawArgs["box"].IndexCount;
	altRenderer->StartIndexLocation = altRenderer->Geo->DrawArgs["box"].StartIndexLocation;
	altRenderer->BaseVertexLocation = altRenderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}
