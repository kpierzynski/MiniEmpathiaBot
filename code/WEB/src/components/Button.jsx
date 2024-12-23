function PrimaryButton({ onClick, children }) {
	return (
		<button
			onClick={onClick}
			className="border border-primary-500 bg-primary-500 text-white p-2 rounded transition duration-100 hover:translate-y-[2px] active:translate-y-[4px]"
		>
			{children}
		</button>
	);
}

function SecondaryButton({ onClick, children }) {
	return (
		<button
			onClick={onClick}
			className="border border-primary-500 p-2 rounded hover:bg-primary-500 hover:text-white transition duration-100"
		>
			{children}
		</button>
	);
}

export default function Button({ onClick, children, primary }) {
	if (primary) {
		return <PrimaryButton onClick={onClick}>{children}</PrimaryButton>;
	}

	return <SecondaryButton onClick={onClick}>{children}</SecondaryButton>;
}
