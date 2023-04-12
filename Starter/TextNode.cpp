#include "TextNode.hpp"
#include "Game.hpp"

TextNode::TextNode(Game* game, Type type) : SceneNode(game)
{
	switch (type) {
	case TitleText:
		mSprite = "TitleText";
		break;
	case PauseTitle:
		mSprite = "PauseTitle";
		break;
	case PauseText:
		mSprite = "PauseText";
		break;
	}
}

void TextNode::updateCurrent(const GameTimer& gt)
{
}

void TextNode::drawCurrent(RenderContext context) const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = context.mCurrFrameResource->ObjectCB->Resource();
	auto matCB = context.mCurrFrameResource->MaterialCB->Resource();

	context.cmdList->IASetVertexBuffers(0, 1, &renderer->Geo->VertexBufferView());
	context.cmdList->IASetIndexBuffer(&renderer->Geo->IndexBufferView());
	context.cmdList->IASetPrimitiveTopology(renderer->PrimitiveType);

	//step18
	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(context.mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
	tex.Offset(renderer->Mat->DiffuseSrvHeapIndex, context.mCbvSrvDescriptorSize);

	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + renderer->ObjCBIndex * objCBByteSize;
	D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + renderer->Mat->MatCBIndex * matCBByteSize;

	//step19
	context.cmdList->SetGraphicsRootDescriptorTable(0, tex);
	context.cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
	context.cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

	context.cmdList->DrawIndexedInstanced(renderer->IndexCount, 1, renderer->StartIndexLocation, renderer->BaseVertexLocation, 0);
}

void TextNode::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}
