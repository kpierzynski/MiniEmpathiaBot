export default function NewFeed({ onClick }) {
	return (
		<div
			onClick={onClick}
			className="border-4 border-dashed  border-gray-300 rounded p-2 flex items-center justify-center hover:backdrop-brightness-95 transition duration-200 cursor-pointer"
		>
			<p>Add new stream</p>
		</div>
	);
}
